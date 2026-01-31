FROM gcc:latest

WORKDIR /app

COPY . .

RUN g++ -std=c++17 program.cpp -o program

CMD ["./program"]
