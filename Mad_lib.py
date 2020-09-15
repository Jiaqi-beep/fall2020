'''


https://stackoverflow.com/questions/40647881/skipping-blank-lines-in-read-file-python/40647977
'''
import random

file = open(r"grammar.txt","r")
lines = file.readlines()

def select_nonterminal (nonterm):
    # parameters from [<article>, <noun>, <verb>, <optional_adjective>]
    file = open("grammar.txt","r")
    lines = [line for line in file.readlines() if line.strip()] 
    for line in lines:
        line = line[:-1]
        #print(line)
        if line.split()[0] == nonterm:
            list = line.rsplit("::=")[1].split("|")
            #print(list)
            v = random.choice(list)  
    return v

def object ():
    return subject()

def subject():
    article = select_nonterminal ("<article>")
    optional_adjective = select_nonterminal ("<optional_adjective>")
    noun = select_nonterminal ("<noun>")
    
    if optional_adjective == " EPSILO":
        subj = article + noun
    else:
        subj = article + optional_adjective + noun
    return subj

def sentence ():
    subj = subject()
    verb = select_nonterminal ("<verb>")
    obj = object()
    return subj + verb + obj

def story ():
    sentence1 = sentence()
    sentence2 = sentence()
    sentence3 = sentence()
    story = sentence1 + "." + sentence2 + "." + sentence3 + "." + " the end."
    print(story)
    
if __name__ == "__main__":
    story()