# Important READ:
# This dockerfile is not complete and will not work.
# Running locally us currently the only option
# ToDo: Forward display for gui to work, either virtual framebuffer or forward to X display server
FROM archlinux:latest
RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm \
        openssl \
        libxrandr \
        libxi \
        glfw && \
    pacman -Sc --noconfirm && \
    rm -rf /var/cache/pacman/pkg/*  
COPY . /Corvus
WORKDIR /Corvus
RUN make
ENV XDG_RUNTIME_DIR=/tmp
ENTRYPOINT ["./corvus"]
CMD ["http://www.google.com"]
