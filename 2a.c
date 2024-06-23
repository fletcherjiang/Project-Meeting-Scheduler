if (word_count == 4)
{
    struct Project* iter;
    for (iter = projects; iter != NULL; iter = iter->next)
    {
        if (strcmp(iter->team, words[0]) == 0)
        {
            break;
        }
    }
    if (iter == NULL)
    {
        printf(">>>>>> Wrong input.\n");
    }
    else
    {
        struct Meeting* meeting;
        meeting = (struct Meeting*)malloc(sizeof(struct Meeting));
        meeting->next = NULL;
        meeting->project = iter;
        sscanf(words[1], "%d-%d-%d", &meeting->year, &meeting->month, &meeting->day);
        sscanf(words[2], "%d:%d", &meeting->hour, &meeting->minute);
        sscanf(words[3], "%d", &meeting->duration);
        if(meeting->duration < 1 || meeting->duration > 9 || meeting->hour < 9 || meeting->hour + meeting->duration > 18 || (meeting->hour + meeting->duration == 18 && meeting->minute != 0)
        || meeting->year !=2022 ||meeting->month < 4 ||meeting->month > 5 ||(meeting->month ==4 && (meeting->day<25||meeting->day>30)) ||(meeting->month==5 && meeting->day>14)
        ||(meeting->year==2022&&meeting->month==5&&meeting->day==1)
        ||(meeting->year==2022&&meeting->month==5&&meeting->day==8)

        )
        {
            free(meeting);
            printf(">>>>>> Wrong input.\n");
        }
        else
        {
            meetings = AddMeeting(meetings, meeting);
            printf(">>>>>> Not yet scheduled.\n");
        }
    }
}
