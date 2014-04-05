#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{

    int i,ch;
    char ch_name[25];
    int val=-1,num_domains;
    int *active_domains;

    virConnectPtr conn;
    virDomainPtr vdp;

    conn = virConnectOpen("xen:///");

    if (conn == NULL) 
    {
        fprintf(stderr, "Error opening connection to XEN:/// \n");
        return 1;
    }
    else
    {

        num_domains = virConnectNumOfDomains(conn);
        active_domains = malloc(sizeof(int) * num_domains);
        num_domains = virConnectListDomains(conn, active_domains, num_domains);

        printf("Active domain IDs : \n");
        for (i = 0 ; i < num_domains ; i++) 
        {
            printf(" %d\n", active_domains[i]);
        }
        free(active_domains);

        while(1)
        {
            printf("\n");
            printf("1.Start\n2.Suspend\n3.Resume\n4.stop\n5.exit ");
            scanf("%d",&ch);

            if(ch<5)
            {  
               printf("\n Please Insert the Active Domian Name ");
               scanf("%s",&ch_name);
               vdp=virDomainLookupByName(conn,ch_name);
            }
            
            switch(ch)
            {
                case 1:/* Start */
                       val = virDomainCreate(vdp);
                       if(val==0)
                           printf("Success\n");
                       else
                           printf("Failed\n");
                       break;
                case 2:/* Suspend */
                       val = virDomainSuspend(vdp);
                       if(val==0)
                           printf("Success\n");
                       else
                           printf("Failed\n");
                       break;
                case 3:/* Resume */
                       val = virDomainResume(vdp);
                       if(val==0)
                           printf("Success\n");
                       else
                           printf("Failed\n");
                       break;

                case 4: /* stop */
		        val =virDomainShutdown(vdp);
                        if(val==0)
                            printf("Success\n");
                        else
                            printf("Failed\n");
                        break;
                default:exit(1);
            }
        }
        virConnectClose(conn);
    }
}


