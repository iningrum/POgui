import sys
import clear_all
import merge
actions = {}
actions["clear"] = clear_all.clear,1
actions["csv"] = merge.merger,2
if __name__ == "__main__":
    if len(sys.argv) >= 2:
        operation,len_args = actions[sys.argv[1]]
        all_args = sys.argv[2:]
        operation(*all_args[:len_args])


    else:
        print(len(sys.argv))


