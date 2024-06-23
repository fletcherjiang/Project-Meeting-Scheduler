void HS(struct Meeting* meetings, struct Staff* staffs, struct Project* projects, int start_year, int start_month, int start_day, int end_year, int end_month, int end_day, FILE *fp)
//create the HS(Humane Sorting)
{
    struct Meeting* result = NULL;
    struct Meeting* rejected = NULL;
    int accepted_count = 0;
    int rejected_count = 0;
    int total_count = 0;
    struct Meeting* iter;
    struct Staff* staff_iter;
    struct Meeting* iter2;
    struct Project* project_iter;
    int start;
    int end;
    start = start_year * 12 * 35 + start_month * 35 + start_day;
    end = end_year * 12 * 35 + end_month * 35 + end_day;
    for (iter = meetings; iter != NULL; iter = iter->next)
    {
        int add = 1;
        total_count += 1;
        if (start <= iter->year * 12 * 35 + iter->month * 35 + iter->day && end >= iter->year * 12 * 35 + iter->month * 35 + iter->day)
        {
            struct Meeting* prev = NULL;
            for (iter2 = result; iter2 != NULL; iter2 = iter2->next)
            {
                if (iter->year * 12 * 35 + iter->month * 35 + iter->day == iter2->year * 12 * 35 + iter2->month * 35 + iter2->day)
                {
                    int start2 = iter->hour * 60 + iter->minute;
                    int end2 = start2 + iter->duration * 60;
                    int start1 = iter2->hour * 60 + iter2->minute;
                    int end1 = start1 + iter2->duration * 60;
                    if (!(end1 <= start2 || end2 <= start1))
                    {
                        // Clash, if crach, iter2 is last meeting
                        // printf("Crash %s %.2d-%.2d-%.2d %.2d:%.2d %d\n", iter->project->team, iter->year, iter->month, iter->day, iter->hour, iter->minute, iter->duration);
                        // printf(" %s %.2d-%.2d-%.2d %.2d:%.2d %d\n", iter2->project->team, iter2->year, iter2->month, iter2->day, iter2->hour, iter2->minute, iter2->duration);
                        // printf("%d %d %d %d\n", start1, end1, start2, end2);
                        if (start1 < 12 * 60 && end1 > 12 * 60 && (start2 >= 12 * 60 || end2 <= 12 * 60))
                        {
                                       struct Meeting* meeting;
                                       meeting = (struct Meeting*)malloc(sizeof(struct Meeting));
                                       if (meeting != NULL)
                                      {
                                          memcpy(meeting, iter2, sizeof(struct Meeting));
                                      meeting->next = NULL;
                                           rejected = AddMeeting(rejected, meeting);
                                                    rejected_count += 1;
                                      }
                                   accepted_count -= 1;
                            if (prev == NULL)
                            {
                                FreeMeetingList(result);
                                result = NULL;
                            }
                            else
                            {
                                FreeMeetingList(prev->next);
                                prev->next = NULL;
                            }
                        }
                        else
                        {
                            add = 0;
                        }
                        break;
                    }
                }
                prev = iter2;
            }
            if (add == 1)
            {
                struct Meeting* meeting;
                meeting = (struct Meeting*)malloc(sizeof(struct Meeting));
                if (meeting != NULL)
                {
                memcpy(meeting, iter, sizeof(struct Meeting));
                meeting->next = NULL;
                result = AddMeeting(result, meeting);
                accepted_count += 1;
                }
            }
            else
            {
                            struct Meeting* meeting;
                            meeting = (struct Meeting*)malloc(sizeof(struct Meeting));
                            if (meeting != NULL)
                            {
                                memcpy(meeting, iter, sizeof(struct Meeting));
                                meeting->next = NULL;
                                rejected = AddMeeting(rejected, meeting);
                                rejected_count += 1;
                            }
            }
        }
    }
    for (staff_iter = staffs; staff_iter != NULL; staff_iter = staff_iter->next)
    {
        printf("\n");
        printf("Date           Start   End       Team          Project\n");
        printf("===========================================================================\n");
        fprintf(fp, "\n");
        fprintf(fp, "Date           Start   End       Team          Project\n");
        fprintf(fp, "===========================================================================\n");
        for (iter = result; iter != NULL; iter = iter->next)
        {
             int i;
             for(i = 0; i < iter->project->member_count; ++i)
             {
                      if(strcmp(iter->project->members[i], staff_iter->name) == 0)
                      {break;}
             }
             if(i < iter->project->member_count)
             {
                printf("%.4d-%.2d-%.2d     %.2d:%.2d    %.2d:%.2d     %-14s %s\n", iter->year, iter->month, iter->day, iter->hour, iter->minute, iter->hour + iter->duration, iter->minute, iter->project->team, iter->project->name);
                fprintf(fp, "%.4d-%.2d-%.2d     %.2d:%.2d    %.2d:%.2d     %-14s %s\n", iter->year, iter->month, iter->day, iter->hour, iter->minute, iter->hour + iter->duration, iter->minute, iter->project->team, iter->project->name);
             }
        }
        printf("===========================================================================\n");
        printf("Staff: %s\n", staff_iter->name);
        fprintf(fp, "===========================================================================\n");
        fprintf(fp, "Staff: %s\n", staff_iter->name);
    }
    printf("\n*** Meeting Request – REJECTED ***\n");
    printf("There are %d requests rejected for the required period.\n", rejected_count);
    fprintf(fp, "\n*** Meeting Request – REJECTED ***\n");
    fprintf(fp, "There are %d requests rejected for the required period.\n", rejected_count);
    rejected_count = 0;
    printf("===========================================================================\n");
    fprintf(fp, "===========================================================================\n");
    for (iter = rejected; iter != NULL; iter = iter->next)
    {
          rejected_count += 1;
    printf("%d.  %s %.4d-%.2d-%.2d %.2d:%.2d %d\n", rejected_count, iter->project->name, iter->year, iter->month, iter->day, iter->hour, iter->minute, iter->duration);
    fprintf(fp, "%d.  %s %.4d-%.2d-%.2d %.2d:%.2d %d\n", rejected_count, iter->project->name, iter->year, iter->month, iter->day, iter->hour, iter->minute, iter->duration);
    }
    printf("===========================================================================\n");
    fprintf(fp, "===========================================================================\n");
    
    printf("Performance:\n\n");
    printf("Total Number of Requests Received: %d (%.1lf%%)\n", rejected_count + accepted_count, (double)(rejected_count + accepted_count) * 100.0 / (double)total_count);
    printf("      Number of Requests Accepted: %d (%.1lf%%)\n", accepted_count, (double)accepted_count * 100.0 / (double)(rejected_count + accepted_count));
    printf("      Number of Requests Rejected: %d (%.1lf%%)\n", rejected_count, (double)rejected_count * 100.0 / (double)(rejected_count + accepted_count));
    printf("\n");
    printf("Utilization of Time Slot:\n\n");
    printf("     Accepted request        - %.1lf%%\n", (double)accepted_count * 100.0 / (double)(rejected_count + accepted_count));
    fprintf(fp, "Performance:\n\n");
    fprintf(fp, "Total Number of Requests Received: %d (%.1lf%%)\n", rejected_count + accepted_count, (double)(rejected_count + accepted_count) * 100.0 / (double)total_count);
    fprintf(fp, "      Number of Requests Accepted: %d (%.1lf%%)\n", accepted_count, (double)accepted_count * 100.0 / (double)(rejected_count + accepted_count));
    fprintf(fp, "      Number of Requests Rejected: %d (%.1lf%%)\n", rejected_count, (double)rejected_count * 100.0 / (double)(rejected_count + accepted_count));
    fprintf(fp, "\n");
    fprintf(fp, "Utilization of Time Slot:\n\n");
    fprintf(fp, "     Accepted request        - %.1lf%%\n", (double)accepted_count * 100.0 / (double)(rejected_count + accepted_count));
    for (project_iter = projects; project_iter != NULL; project_iter = project_iter->next)
    {
        int all_count = 0;
        int acc_count = 0;
        for (iter = meetings; iter != NULL; iter = iter->next)
        {
              if(iter->project == project_iter)
              {
                 if (start <= iter->year * 12 * 35 + iter->month * 35 + iter->day && end >= iter->year * 12 * 35 + iter->month * 35 + iter->day)
                  {
                    all_count += 1;
                  }
              }
        }
        if(all_count > 0) 
        {
                       for (iter = result; iter != NULL; iter = iter->next)
              {
                       if(iter->project == project_iter)
                       {
                     acc_count += 1;
                       }
        }
              printf("     %-20s    - %.1lf%%\n", project_iter->team, (double)acc_count * 100.0 / (double)all_count);
              fprintf(fp, "     %-20s    - %.1lf%%\n", project_iter->team, (double)acc_count * 100.0 / (double)all_count);
        }
    }
    printf("\n");
    fprintf(fp, "\n");
    for (staff_iter = staffs; staff_iter != NULL; staff_iter = staff_iter->next)
    {
              int all_count = 0;
              int acc_count = 0;
              for (iter = meetings; iter != NULL; iter = iter->next)
              {
                   if(StaffInProject(iter->project, staff_iter))
                    {
                      if (start <= iter->year * 12 * 35 + iter->month * 35 + iter->day && end >= iter->year * 12 * 35 + iter->month * 35 + iter->day)
                            {
                          all_count += 1;
                      }
                    }
              }
        if(all_count > 0) 
        {
                        for (iter = result; iter != NULL; iter = iter->next)
                        {
                              if(StaffInProject(iter->project, staff_iter))
                              {acc_count += 1;}
                  }
                        printf("     %-20s    - %.1lf%%\n", staff_iter->name, (double)acc_count * 100.0 / (double)all_count);
                  fprintf(fp, "     %-20s    - %.1lf%%\n", staff_iter->name, (double)acc_count * 100.0 / (double)all_count);
        }
    }
    printf("\n");
    printf("Attendance:\n\n");
    fprintf(fp, "\n");
    fprintf(fp, "Attendance:\n\n");
    for (staff_iter = staffs; staff_iter != NULL; staff_iter = staff_iter->next)
    {
        int i;
        int all_count = end_day - start_day + 1;
        int atten_count = 0;
        int year, month, day;
        if(start_month != end_month)
        {
            all_count += 30;
        }
        year = start_year;
        month = start_month;
        day = start_day;
        for(i = 0; i < all_count; ++i)
        {
            for (iter = result; iter != NULL; iter = iter->next)
            {
                if(iter->year == year && iter->month == month && iter->day == day && StaffInProject(iter->project, staff_iter))
                {
                    atten_count += 1;
                    break;
                }
            }
            day += 1;
            if(day == 31) 
            {
                month += 1;
                day = 1;
            }
        }
        printf("     %-20s    - %.1lf%%\n", staff_iter->name, (double)atten_count * 100.0 / (double)all_count);
        fprintf(fp, "     %-20s    - %.1lf%%\n", staff_iter->name, (double)atten_count * 100.0 / (double)all_count);
    }
    
    while (rejected != NULL)
    {
        struct Meeting* meeting = rejected->next;
        free(rejected);
        rejected = meeting;
    }
    while (result != NULL)
    {
        struct Meeting* meeting = result->next;
        free(result);
        result = meeting;
    }
}
