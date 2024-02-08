import socket

SERVER_IP = "192.168.1.17"
SERVER_PORT = 9999
#create a TCP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# enable TCP keep-alive
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)

# Set the TCP keep-alive parameters: idle time, interval, and count
client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, 10)  # Idle time in seconds
client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, 5)  # Interval between keep-alive probes in seconds
client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, 2)     # Number of keep-alive probes

# Connect to server
client_socket.connect((SERVER_IP,SERVER_PORT))

print(f"--- Successfully connected to TCP Server at {SERVER_IP}::{SERVER_PORT}")

while True:
    try:
        # input message
        message = input(":: ")

        if not message.strip():
            print("** INVALID INPUT **")
            continue
        
        # send the message to SERVER
        client_socket.sendall(message.encode())

        # received the response from SERVER
        response = client_socket.recv(1024).decode()
        print(f">> {response}")
    # recognise termination
    except KeyboardInterrupt:
        client_socket.close()
        print("--- CONNECTION CLOSED ---")
        break
