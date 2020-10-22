FROM golang:1.15-alpine AS builder
RUN apk add git
RUN adduser --disabled-password --gecos '' web300vuln
WORKDIR /src/300

ENV GOPATH=/go
COPY go.mod go.sum ./
RUN go mod download

COPY . .

ENV CGO_ENABLED 0

RUN go build -o /src/300/300 /src/300/*.go
RUN chown -R web300vuln /src/300/webrequests.log


FROM scratch

COPY --from=builder /src/300/300 /300

COPY --from=builder /src/300/index.html /index.html
COPY --from=builder /src/300/config.json /config.json
COPY --from=builder /src/300/webrequests.log /webrequests.log






COPY --from=builder /etc/passwd /etc/passwd

USER web300vuln
ENTRYPOINT [ "/300"]