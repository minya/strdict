#!/usr/bin/python
import uuid

with open('huge.txt', 'w', 4194304) as f:
    for i in range(4194304):
        f.write(uuid.uuid4().hex + '\n')


