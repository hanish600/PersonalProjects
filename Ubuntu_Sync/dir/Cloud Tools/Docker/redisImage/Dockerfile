# Use existing docker base image
FROM alpine

# Download and install a dependency
# Keep the order to use existing cache by adding at eol
RUN apk add --update redis

# What the image will do when container starts
CMD [ "redis-server" ]