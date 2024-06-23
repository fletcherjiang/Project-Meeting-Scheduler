if (option == 1)
{
    char words[20][30];
    char value[100];
    while (1)
    {
        int word_count = 0;
        int start_index = 0;
        printf("Enter> ");
        fgets(value, 100, stdin);
        for (i = 0; value[i] != '\0' && value[i] != '\n'; ++i)
        {
            if (value[i] == ' ')
            {
                value[i] = '\0';
                strcpy(words[word_count], value + start_index);
                start_index = i + 1;
                word_count += 1;
            }
        }
        value[i] = '\0';
        strcpy(words[word_count], value + start_index);
        start_index = i + 1;
        word_count += 1;
        if (word_count == 1 && strcmp(words[0], "0") == 0)
        {
            break;
        }
        if (word_count >= 3)
        {
            int count[20];
            int success = 1;
            struct Project* project;
            struct Project* iter;
            int number=0;
            project = (struct Project*)malloc(sizeof(struct Project));
            project->member_count = word_count - 2;
            if (project->member_count>4)
            {
                success=0;
            }
            
            strcpy(project->team, words[0]);
            strcpy(project->name, words[1]);
            project->next = NULL;
            count[0] = 0;
            for (i = 2; i < word_count; ++i)
            {
                        staffs = AddStaff(staffs, words[i]);
                strcpy(project->members[i - 2], words[i]);
                count[i - 2] = 0;
            }
            for (iter = projects; iter != NULL && success == 1; iter = iter->next)
            {
                if (strcmp(iter->members[0], project->members[0]) == 0)
                {
                    success = 0;
                    break;
                }
                for (i = 0; i < iter->member_count && success == 1; ++i)
                {
                    for (j = 0; j < project->member_count && success == 1; ++j)
                    {
                        if (strcmp(iter->members[i], project->members[j]) == 0)
                        {
                            count[j] += 1;
                            if (count[j] >= 3)
                            {
                                success = 0;
                            }
                        }
                    }
                }
            }
            if (success == 1)
            {
                int number123=0;
                if (projects == NULL)
                {
                    projects = project;
                }
                else
                {

                    struct Project* last = projects;
                    while (last->next != NULL)
                    {
                        last = last->next;
                        number123++;
                
                    }
                    last->next = project;
                    
                }
                
                
                printf(">>>>>> Project %s is created.\n", project->team);
                
                
                

                
            }
            else
            {
                printf(">>>>>> Failed.\n");
                free(project);
            }
        }
        else
        {
            printf(">>>>>> Failed.\n");
        }
    }
}
