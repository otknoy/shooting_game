FROM debian:buster

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev

WORKDIR /app

COPY . .
RUN make

RUN file shooting
