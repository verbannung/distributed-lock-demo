# Distributed Lock Demo

ps:under developing

A lightweight **distributed lock service** implemented in **C++20**, designed as a learning-oriented middleware project.  
It demonstrates **event-driven networking (epoll/kqueue)**, **custom JSON protocol parsing**, and a **LockManager** with TTL expiration.

---

## ✨ Features
- **Event-driven TCP server**
  - Supports both **epoll (Linux)** and **kqueue (macOS/BSD)**
  - Handles multiple concurrent client connections
- **Custom protocol**
  - Requests and responses use **JSON**
  - Commands supported:
    - `ACQUIRE` (try to acquire a lock)
    - `RELEASE` (release a lock)
- **LockManager**
  - In-memory lock table
  - TTL (time-to-live) expiration
- **RequestHandler**
  - Parses protocol
  - Delegates to `LockManager`
  - Builds JSON responses
- **Testing**
  - Integrated with **GoogleTest**
  - Unit tests for `LockManager` and server components

---

## 📂 Project Structure