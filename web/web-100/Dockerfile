FROM golang:1.15-alpine AS builder
RUN apk add git
RUN adduser --disabled-password --gecos '' web100vuln
WORKDIR /src/100

ENV GOPATH=/go
COPY go.mod go.sum ./
RUN go mod download

COPY . .

ENV CGO_ENABLED 0

RUN go build -o /src/100/100 /src/100/*.go


FROM scratch

COPY --from=builder /src/100/100 /100
COPY --from=builder /src/100/static/* /static/
COPY --from=builder /src/100/index.html /index.html
COPY --from=builder /src/100/config.json /config.json





COPY --from=builder /etc/passwd /etc/passwd

USER web100vuln
ENTRYPOINT [ "/100"]