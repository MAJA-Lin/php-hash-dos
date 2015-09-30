#!/usr/bin/python3

import json
import sys

s = sys.stdin.read()
obj = json.loads(s)
for k in obj.keys():
    print("%s => " % k)
