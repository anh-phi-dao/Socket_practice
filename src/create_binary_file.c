#include <stdio.h>

FILE *fileptr;
char string[1024];
int main()
{
    fileptr = fopen("Viettel.txt", "wb");

    sprintf(string, "Viettel Group's pinnacle affiliate Viettel Telecom is currently the dominant network operator with the largest market share in Vietnamese telecommunications services market.[5] For 30 years, Viettel has grown from a construction company to a complex of five business lines including telecommunications and information technology (IT); research and manufacture of electronic and telecommunications equipment; defense industry; cyber security and digital services. Viettel is considered one of the largest and most effective state-owned enterprises of Vietnam, thanks to its high revenue, large contribution to the State budget and high brand value");

    fputs(string, fileptr);

    fclose(fileptr);

    fileptr = fopen("Viettel_High_Tech.txt", "wb");

    sprintf(string, "Viettel High Technology Industries Corporation is the key research and production unit of Viettel specialized in military and civilian sectors, who has successfully internalized a complete process from researching, designing to manufacturing and selling cutting edge technology solutions. Armed with a team of talented and experienced professionals; a culture that value collaboration and forward thinking, we envision ourselves as a modern, intellectual abundant technology company whose brand is recognized across the globe");

    fclose(fileptr);

    return 0;
}