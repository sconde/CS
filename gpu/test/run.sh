#!/bin/bash

docker build -t ubuntu-nvidia . && \
    docker run -it \
    -v $(pwd):/home \
    --device /dev/nvidia0:/dev/nvidia0 \
    --device /dev/nvidiactl:/dev/nvidiactl \
    --device /dev/nvidia-uvm:/dev/nvidia-uvm \
    ubuntu-nvidia /bin/bash

