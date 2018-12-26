SDL_Surface* pSprite = SDL_LoadBMP("./sprites/grass.bmp");
if ( pSprite )
{
    SDL_Rect dest = { 640/2 - pSprite->w/2,480/2 - pSprite->h/2, 0, 0};
    SDL_BlitSurface(pSprite,NULL,SDL_GetWindowSurface(pWindow),&dest); // Copie du sprite

    SDL_UpdateWindowSurface(pWindow); // Mise � jour de la fen�tre pour prendre en compte la copie du sprite
    SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fen�tre */

    SDL_FreeSurface(pSprite); // Lib�ration de la ressource occup�e par le sprite
}
else
{
    fprintf(stdout,"�chec de chargement du sprite (%s)\n",SDL_GetError());
}
