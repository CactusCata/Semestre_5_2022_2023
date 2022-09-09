class Queue:

    def __init__(self):
        self.queue = []

    def enqueue(self, x):
        self.queue.append(x)

    def dequeue(self):
        if self.getQueueSize() > 0:
            value = self.queue[0]
            newQueue = [None] * (self.getQueueSize() - 1)
            for i in range(self.getQueueSize() - 1):
                newQueue[i] = self.queue[i + 1]
            self.queue = newQueue
            return value

    def getQueueSize(self):
        return len(self.queue)

    def __str__(self):
        return str(self.queue)

if __name__ == "__main__":
    queue = Queue()
    print(queue)
    queue.enqueue(5)
    queue.enqueue(2)
    queue.enqueue(-1)
    print(queue)
    print(f"top of queue = {queue.dequeue()}")
    print(queue)
    print(f"top of queue = {queue.dequeue()}")
    print(queue)
    print(f"top of queue = {queue.dequeue()}")
    print(queue)
    print(f"top of queue = {queue.dequeue()}")
    print(queue)
