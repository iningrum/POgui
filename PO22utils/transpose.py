"""
    Script that makes our inproper csv file into proper one.
"""


class File:
    result: list

    def __init__(self, src: str):
        self.result = []
        with open(src) as f:
            result = f.readlines()
        if result:
            result = [line.strip().split(',') for line in result]
            lines = ""
            for i in range(len(result[0])):
                self.result.append(",".join([line[i] for line in result])+"\n")
                lines = "".join(self.result)
            with open(src,"w") as f:
                f.write(lines)
        else:
            raise ValueError("File is empty")
