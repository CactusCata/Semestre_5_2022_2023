class Stack():

    def __init__(self):
        self.stack = []

    def push(self, x):
        self.stack.append(x)

    def pop(self):
        if self.getStackSize() > 0:
            topOfStack = self.stack[len(self.stack) - 1]
            self.stack = self.stack[:len(self.stack) - 1]
            return topOfStack

    def getStackSize(self):
        return len(self.stack)

    def __str__(self):
        return str(self.stack)

if __name__ == "__main__":
    stack = Stack()
    print(stack)
    stack.push(5)
    stack.push(2)
    stack.push(-1)
    print(stack)
    print(f"top of stack = {stack.pop()}")
    print(stack)
    print(f"top of stack = {stack.pop()}")
    print(stack)
    print(f"top of stack = {stack.pop()}")
    print(stack)
    print(f"top of stack = {stack.pop()}")
    print(stack)
