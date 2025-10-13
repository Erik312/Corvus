# Important READ:
# This dockerfile is not complete and will not work.
# Running locally us currently the only option
# ToDo: forward display for gui to work either virtual framebuffer or forward to X display server
FROM gcc:latest
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        libssl-dev \
        libxrandr-dev \
        libxi-dev \
        libglfw3-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*  
COPY . /Corvus
WORKDIR /Corvus
RUN make
ENV XDG_RUNTIME_DIR=/tmp
ENTRYPOINT ["./corvus"]
CMD ["http://www.google.com"]
