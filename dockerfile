# Base image (x86_64 Ubuntu)
FROM --platform=linux/amd64 ubuntu:latest

# Install NASM and build tools
RUN apt update && apt install -y nasm build-essential file

# Default shell
CMD ["/bin/bash"]
