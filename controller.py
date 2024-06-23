import sys
from model import Model
from view import View
"""
The Controller class translates user actions into operations on the Model,
although it depends on command line interface to read keystrokes.
"""
class Controller:
    def __init__(self, model : Model, view : View) -> None:
        self.model = model
        self.view = view
    
    def run(self):
        self.model.init() # read all info from txt, and store it into storage.
        while True:
            self.view.entry_page()
            x = self.view.read_input()
            if x == '1': # CLI
                while True:
                    self.view.command_line()
                    which = self.view.read_input()
                    if which == '1': # user login
                        id = self.view.id_validation()
                        self.view.user_page()
                        manner = self.view.read_input()
                        if manner == '1': # change password
                            new = self.view.new_pass() # password analysis???
                            self.model.update_password(id, new)
                            self.view.valid()
                            # self.model.update_password()
                        if manner == '2': # check current vaccination record
                            return 0
                        if manner == '3':
                            return 0
                        if manner == '4':
                            break
                        if manner == '5':
                            sys.exit()
                        else:
                            self.view.inv_info()
                    if which == '2': # admin login
                        return 0
                    if which == '3': # registration
                        print("are you a student or staff?, 1 -> student, 0 -> staff")
                        who = input()
                        if who == '1':
                            print("Please input your student identity card nuber: ")
                            id_num = input().strip()
                            # format checking, 8 bits of number and 1 bit of alphabet
                            
                            
                        return 0
                    if which == '4':
                        break
                    if which == '5':
                        sys.exit()
                    else:
                        self.view.inv_info()
            if x == '2': # GUI
                return 0
            elif x == '3':
                return 0
            else:
                self.view.inv_info()
                
            
        
        