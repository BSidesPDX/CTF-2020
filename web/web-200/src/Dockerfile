FROM golang:1.15-alpine AS builder
RUN apk add git
RUN adduser --disabled-password --gecos '' web200vuln
WORKDIR /src/200

ENV GOPATH=/go
COPY go.mod go.sum ./
RUN go mod download

COPY . .
RUN chown -R web200vuln /src/200/static

ENV CGO_ENABLED 0

RUN go build -o /src/200/200 /src/200/*.go


FROM scratch

COPY --from=builder /src/200/200 /200
COPY --from=builder /src/200/static/ /static/
COPY --from=builder /src/200/index.html /index.html
COPY --from=builder /src/200/config.json /config.json
COPY --from=builder /src/200/robots.txt /robots.txt





COPY --from=builder /etc/passwd /etc/passwd

USER web200vuln
ENTRYPOINT [ "/200"]