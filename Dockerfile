FROM ubuntu:24.04

# Install sudo and create a user with the same UID and GID as the host
ARG USER_ID
ARG GROUP_ID

RUN apt-get update && apt-get install -y sudo && \
    useradd -u $USER_ID -g $GROUP_ID -m myuser && \
    passwd -d myuser && \
    usermod -aG sudo myuser

# Set the user for future sessions
USER myuser
WORKDIR /home/myuser
