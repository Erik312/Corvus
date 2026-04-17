# Important READ:
# This dockerfile is based on archlinux

FROM archlinux:latest
RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm \
        gcc \
        openssl \
        libxrandr \
        libxi \
        glfw  \
        libx11 \
        libxext \
        libxrender \
        xorg-xauth \
        xorg-xhost && \
    pacman -Sc --noconfirm && \
    rm -rf /var/cache/pacman/pkg/*
COPY . /Corvus
WORKDIR /Corvus
RUN make
ENV DISPLAY=:0
ENV XDG_RUNTIME_DIR=/tmp
ENTRYPOINT ["./corvus"]
CMD ["http://www.example.org"]
