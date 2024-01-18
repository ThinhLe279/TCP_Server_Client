import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 9999

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
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