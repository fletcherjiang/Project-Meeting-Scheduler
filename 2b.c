else if (word_count == 1)  
    {
    FILE* fp = fopen(words[0], "rt");
    if (fp == NULL)
    {
    printf(">>>>>> File not found.\n");
    }
    else
    {
    while (fscanf(fp, "%s %s %s %s", words[2], words[3], words[4], words[5]) > 0)
    {
        struct Project* iter;
        for (iter = projects; iter != NULL; iter = iter->next)
        {
            if (strcmp(iter->team, words[2]) == 0)
            {
                break;
            }
        }
        if (iter == NULL)
        {
            printf(">>>>>> %s %s %s %s: Wrong input.\n", words[2], words[3], words[4], words[5]);
        }
        else
        {
            struct Meeting* meeting;
            meeting = (struct Meeting*)malloc(sizeof(struct Meeting));
            meeting->next = NULL;
            meeting->project = iter;
            sscanf(words[3], "%d-%d-%d", &meeting->year, &meeting->month, &meeting->day);
            sscanf(words[4], "%d:%d", &meeting->hour, &meeting->minute);
            sscanf(words[5], "%d", &meeting->duration);
              if(meeting->duration < 1 || meeting->duration > 9 || meeting->hour < 9 || meeting->hour + meeting->duration > 18 || (meeting->hour + meeting->duration == 18 && meeting->minute != 0)
            || meeting->year !=2022 ||meeting->month < 4 ||meeting->month > 5 ||(meeting->month ==4 && (meeting->day<25||meeting->day>30)) ||(meeting->month==5 && meeting->day>14)
            ||(meeting->year==2022&&meeting->month==5&&meeting->day==1)
                        ||(meeting->year==2022&&meeting->month==5&&meeting->day==8))
              {
                        free(meeting);
            printf(">>>>>> %s %s %s %s: Wrong input.\n", words[2], words[3], words[4], words[5]);
              }
              else
              {
                        meetings = AddMeeting(meetings, meeting);
            printf(">>>>>> %s %s %s %s: Not yet scheduled.\n", words[2], words[3], words[4], words[5]);
              }
        }
    }
    fclose(fp);
    }
    }
