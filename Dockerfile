# C++ development environment
FROM gcc:12-bookworm

# Install development tools
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    gdb \
    make \
    cmake \
    vim \
    nano \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /workspace

# Copy project files
COPY . /workspace/

# Default to bash shell for development
CMD ["/bin/bash"]