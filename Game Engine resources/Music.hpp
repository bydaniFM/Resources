/*
	Daniel Fernández Marqués
*/

#pragma once

#include <SDL.h>
#include <ciso646>
#include <SDL_mixer.h>

class Music{
	
	private:
	
	Mix_Music * music;
	string 		file_path;
	
	public:
	
	Music(){
		
		if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
			SDL_Log ("No se ha podido inicializar SDL2.");
		}else{
			if (Mix_OpenAudio (22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0){
				SDL_Log ("No se ha podido inicializar el subsistema de audio.");
			}else{
				music = nullptr;
			}
		}
	}
	Music(string file_path){
		
		Music();
		
		if(not (music = Mix_LoadMUS (file_path))){
			SDL_Log ("No se ha podido cargar el audio.");
		}else{
			this.file_path = file_path;
		}
		
	}
	
	~Music(){
		if (music) Mix_FreeMusic (music);
	}
	
	Play(Music * music){
		Mix_PlayMusic(music, 1);
	}
	/*Loops:
		number of times to play through the music.
		0 plays the music zero times...
		-1 plays the music forever (or as close as it can get to that)
	*/
	Play(Music * music, int loops){
		Mix_PlayMusic(music, loops);
	}
	Play(Music * music, int loops, int fade){
		Mix_FadeInMusic(music, loops, fade);
	}
	
};