'''
CS313 Homework 1 Madlib

External source:
https://stackoverflow.com/questions/40647881/skipping-blank-lines-in-read-file-python/40647977
'''
import random

def select_nonterminal (nonterm):
    # create nonterminals that are made up of only terminals
    
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
    # create nonterminal <object>
    
    return subject()

def subject():
    # create nonterminal <subject>
    
    select = random.choice([1,2,3])
    # The list denotes the three choices to create nonterminal <subject>
    
    art = article()
    optional_adj = adjective()
    
    if select == 1:
        noun = noun_one()
        subj = art + optional_adj + noun

    elif select == 2:
        subj = art + noun_two()
        
    else:
        noun = noun_three()
        subj = art + optional_adj + noun
    
    return subj

def sentence ():
    # create nonterminal <sentence>
    
    select = random.choice([1,2])
    # Choose between two options to create <sentence> nonterminal
    
    sent = ""
    subj = subject()
    vrb = verb()
    adv = adverb()
    obj = object()
    prp = prep()
    plce = place()
    
    sent += subj + adv + vrb + obj + "."
        
    if select == 2:
        sent = prp + plce + ", " + sent
    return sent

def article ():
    # create nonterminal <article>
    
    art = select_nonterminal ("<article>")
    return art

def prep ():
    # create nonterminal <prep>
    
    prp = select_nonterminal ("<prep>")
    return prp

def place ():
    # create nonterminal <place>
    
    plce = select_nonterminal ("<place>")
    return plce

def noun_one ():
    # create nonterminal <noun_one>
    
    n_two = select_nonterminal ("<noun_one>")
    return n_two

def noun_two ():
    # create nonterminal <noun_two>
    
    n_three = select_nonterminal ("<noun_two>")
    return n_three

def noun_three ():
    # create nonterminal <noun_three>
    
    n_three = select_nonterminal ("<noun_three>")
    return n_three

def verb ():
    # create nonterminal <verb>
    
    v = select_nonterminal ("<verb>")
    return v

def occurrence ():
    # create nonterminal <occurence>
    
    oc = select_nonterminal ("<occurrence>")
    return oc

def phrase ():
    # create nonterminal <phrase>
    
    ph = select_nonterminal ("<phrase>")
    return ph

def adjective ():
    # create nonterminal <optional_adjective>
    
    adj = select_nonterminal ("<optional_adjective>")
    if adj == " EPSILON":
        adj = ""
    return adj

def adverb ():
    # create nonterminal <optional_adverb>
    
    adv = select_nonterminal ("<optional_adv>")
    if adv == " EPSILON":
        adv = ""
    return adv

def dedication():
    # create nonterminal <dedication>

    noun1 = noun_one()
    noun2 = noun_two()
    noun3 = noun_three()
    vrb = verb()
    occrc = occurrence()
    phrse = phrase()
    adj = adjective()
    dedication = "This poem is dedicated to" + \
                 noun2 + " who told me to" + phrse + "," + \
                 noun3 + " who" + vrb + noun2 + ", and" + \
                 noun1 + " without whom I would be" + adj + "."
    
    return dedication

def story ():
    #create the nonterminal <story>
    
    ded = dedication()
    sentence1 = sentence()
    sentence2 = sentence()
    sentence3 = sentence()
    sentence4 = sentence()
    sentence5 = sentence()
    
    poem = sentence1 + "\n" + sentence2 + "\n" + sentence3 + "\n" + sentence4 + "\n" + sentence5 + "\n"
    
    print(ded + "\n\n" + poem)
    
if __name__ == "__main__":
    story()
