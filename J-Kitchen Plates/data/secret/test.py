
class Node:
    def __init__(self,char):
        self.val = char
        self.links = []

def traverse(node,visited,mylist):


    if node.val in visited:
        return []

    visited.add(node.val)
    mylist.append(node.val)


    if len(visited) == 5:
        return mylist

    if len(node.links)==0:
        return []

    res = []

    for shit in node.links:
        new = visited.copy()
        new1 = mylist.copy()
        res.append(traverse(shit,new,new1))

    print("res is %s "%res)
    for stuff in res:
        if len(stuff)>0:
            return stuff
    return []


nodes = {}
nodes["A"] = Node("A")
nodes["B"] = Node("B")
nodes["C"] = Node("C")
nodes["D"] = Node("D")
nodes["E"] = Node("E")



for _ in range(5):

    line = input()
    if line[1] == ">":
        nodes[line[2]].links.append(nodes[line[0]])
    else:
        nodes[line[0]].links.append(nodes[line[2]])

flag = True

for shit in nodes:
    thisnode = nodes[shit]
    res = traverse(thisnode,set(),[])
    if len(res)>0:
        string = ""
        for char in res:
            string+=char
        print(string)
        flag = False
        break
if flag:
    print("impossible")


