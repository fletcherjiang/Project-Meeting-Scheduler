def __init__(self):
        self.info = []
        '''[user id, last name, first name, department, number of injection
            (-1 means fully vaccinated),[injection info],'studentornot']'''
        self.pass_info = []
        '''[user id, password]'''

        '''[the name of recognized vaccines, ... ] the admin will update the
            list of recognized vaccines according to the latest information
            from Hong Kong government. Only the recognized vaccines can be
            recorded in the file system. '''
        self.rec_vac = [] 

        self.admin_password = '' # password of admin

        self.id = dict()
        self.dpt = defaultdict(list)
        '''a dictionary which's key is department, admin can search the
            department to get the information of its students and stuffs'''
        self.isInjected = defaultdict(list)
        ''' a dictionary which's key is number of injection, admin can get
            the information that who have not been inejected'''
        self.userIndex = defaultdict(list)
        '''a dictionary help to get the one user's index of info[] and
            pass_info[], which can help update the information quickly'''
        self.password = dict() 
        '''a dictionary help to confirm the user's password'''

