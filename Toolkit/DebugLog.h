#ifndef DEBUGLOG_H_INCLUDED
#define DEBUGLOG_H_INCLUDED



void Debug_Write_log( (char *) strtolog )
{
    FILE *pFile;
    pFile = fopen( "/documents/Widget/Logger.txt.tns", "a" );
    if (pFile==NULL)
    {
        return;
    }
    fprintf( pFile, "%s\n", strtolog );
    fclose( pFile );
}



#endif // DEBUGLOG_H_INCLUDED
