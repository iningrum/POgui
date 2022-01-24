import os
import transpose
class File:
    def __init__(self,src: str):
        self.content = []
        self.name = src.split('/')[-1]
        with open(src) as f:
            self.content = [ line.strip()[:-1].split(',') for line in f.readlines()]
        self.content = [val for line in self.content for val in line]

def merger(input_src,output_src):
    files = [File(input_src+name) for name in os.listdir(input_src)]
    lines = [obj.name+','+",".join(obj.content) for obj in files if "time" not in obj.name]
    time = [obj for obj in files if "time" in obj.name]
    for obj in time:
        obj.content = [val for val in obj.content if val]
    time = [obj.name+','+','.join(obj.content) for obj in time]
    lines = time+lines
    lines = "\n".join(lines)
    with open(output_src,"w") as f:
        f.write(lines)
    transpose.File(output_src)
#merger("/home/pontiff/CppProjects/PO22/ty/POgui/readings/","/home/pontiff/CppProjects/PO22/ty/POgui/results.csv")