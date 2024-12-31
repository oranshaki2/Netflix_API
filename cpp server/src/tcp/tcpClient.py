import socket
import sys

def main():
    # Ensure the client is called with the correct number of arguments
    if len(sys.argv) != 3:
        print("Usage: python client.py <server_ip> <server_port>")
        sys.exit(1)

    # Get the server's IP and port
    server_ip = sys.argv[1]
    server_port = int(sys.argv[2])

    try:
        # Create a TCP socket
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect to the server
        client_socket.connect((server_ip, server_port))

        # Send commands and receive responses
        while True:
            # Get command input from the user
            command = input("")  
            if command == "":
                command = " "

            # Send the command to the server
            client_socket.sendall(bytes(command, 'utf-8'))

            # Wait for the server's response
            # Buffer size of 4096 bytes
            response = client_socket.recv(4096) 
                 
            if not response:
                # Server closed the connection
                break

            # Print the server's response
            print(response.decode('utf-8'))

    finally:
        # Close the socket
        client_socket.close()

if __name__ == "__main__":
    main()