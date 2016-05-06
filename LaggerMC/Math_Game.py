import operator
import random

operations = {
    "addition": ("+", operator.add),
    "substraction": ("-", operator.sub),
    "multiplication": ("*", operator.mul),
    "division": ("/", operator.floordiv),
}

def ask_operation(difficulty, maxtries=3):
    maxvalue = 5 * difficulty
    x = random.randint(1, maxvalue)
    y = random.randint(1, maxvalue)
    op_name, (op_symbol, op_fun) = random.choice(list(operations.items()))
    result = op_fun(x, y)

    print("Difficulty level %d" % difficulty)
    print("Now lets do a %s calculation and see how clever you are." % op_name)
    print("So what is %d %s %d?" % (x, op_symbol, y))

    for ntry in range(1, 1+maxtries):
        answer = int(input(">"))
        if answer == result:
            print("Correct!")
            return True
        elif ntry == maxtries:
            print("That's %s incorrect answers.  The end." % maxtries)
        else:
            print("That's not right.  Try again.")
    return False

def play(difficulty):
    while ask_operation(difficulty):
        difficulty += 1
    print("Difficulty level achieved: %d" % difficulty)

play(1)