# Use a base image with a C development environment
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /usr/src/bank_app

# Copy the project files into the container
COPY . .

# Compile the project
RUN make

# Run the executable when the container starts
ENTRYPOINT ["./bank_app"]
