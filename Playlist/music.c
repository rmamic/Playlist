#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<stdbool.h>

#define MAX 120

typedef struct music* Song;
typedef struct music {
	char song[MAX];
	char artist[MAX];
	char hashtags[MAX];
	Song next;
}Music;

Song Alokacija();
void ProcitajDatoteku(Song);
void DodajNovi(Song, char[], char[], char[]);
void DodajuDatoteku(char[], char[], char[]);
void Ispis(Song);
void Izbornik();
bool DodajPjesmu(Song);
void PretragaPoImenu(Song, char[]);
void PretragaPoIzvodacu(Song, char[]);
void PretragaPoHashtagu(Song, char[]);
bool JeLiHashtag(char[], char[]);

int main()
{
	Song head;
	head = Alokacija();
	int izbor;
	bool test = false;
	char buffer[MAX], buff[5];
	ProcitajDatoteku(head);

	do
	{
		Izbornik();
		scanf("%d", &izbor);
		switch (izbor)
		{
		case 1:
			test = DodajPjesmu(head);
			if (test)
				printf("Pjesma je uspjesno dodana!\n");
			else
				printf("Nesto je poslo po zlu, pokusajte ponovno!\n");
			break;
		case 2:
			printf("Unesite ime pjesme: ");
			fgets(buff, sizeof(buff), stdin);
			fgets(buffer, MAX, stdin);
			PretragaPoImenu(head, buffer);
			break;
		case 3:
			printf("Unesite ime izvodaca: ");
			fgets(buff, sizeof(buff), stdin);
			fgets(buffer, MAX, stdin);
			PretragaPoIzvodacu(head, buffer);
			break;
		case 4:
			printf("Unesite hashtag: ");
			fgets(buff, sizeof(buff), stdin);
			fgets(buffer, MAX, stdin);
			PretragaPoHashtagu(head, buffer);
			break;
		case 5:
			Ispis(head);
			break;
		case 0:
			return 0;
		default:
			printf("Krivi unos, molimo pokusajte ponovno: \n");
			break;
		}
		printf("\n Pritisnite bilo koju tipku za nastavak...");
		system("pause>nul");
		system("cls");
	} while (izbor);


	return 0;
}

Song Alokacija()
{
	Song novi;
	novi = (Song)malloc(sizeof(Music));
	strcpy(novi->artist, "");
	strcpy(novi->hashtags, "");
	strcpy(novi->song, "");
	novi->next = NULL;
	return novi;
}

void ProcitajDatoteku(Song head)
{
	FILE* fp;
	fp = fopen("playlist.txt", "r");


	if (fp == NULL)
	{
		printf("Datoteka ne postoji, prilikom dodavanja pjesme stvara se datoteka playlist.txt...\n\n");
		return;
	}

	char song[MAX] = "";
	char artist[MAX] = "";
	char hashtags[MAX] = "";

	while (!feof(fp))
	{
		fgets(song, MAX, fp);
		fgets(artist, MAX, fp);
		fgets(hashtags, MAX, fp);

		DodajNovi(head, song, artist, hashtags);

		memset(song, 0, sizeof(song));
		memset(artist, 0, sizeof(artist));
		memset(hashtags, 0, sizeof(hashtags));
	}

	fclose(fp);

}

void DodajNovi(Song head, char song[], char artist[], char hashtags[])
{
	Song novi = Alokacija();
	if (!strcmp(song, "") || !strcmp(artist, "") || !strcmp(hashtags, ""))
	{
		return;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		strcpy(novi->artist, artist);
		strcpy(novi->hashtags, hashtags);
		strcpy(novi->song, song);
		head->next = novi;
	}

}

void Ispis(Song temp)
{
	if (temp->next == NULL)
		printf("Lista je prazna!\n");
	else
	{
		temp = temp->next;
		while (temp != NULL)
		{
			printf("\nIme pjesme:\t%s\n", temp->song);
			printf("Ime izvodaca:\t%s\n", temp->artist);
			printf("Hashtags:\t%s\n\n", temp->hashtags);
			temp = temp->next;
		}
	}
}

void Izbornik()
{
	printf("----------------------------------------\n");
	printf("<1. Dodavanje pjesme>\n");
	printf("<2. Pretraga po imenu pjesme>\n");
	printf("<3. Pretraga po izvodacu>\n");
	printf("<4. Pretraga po hashtagu>\n");
	printf("<5. Ispis playliste>\n");
	printf("<0. Izlaz>\n");
	printf("//Svaku rijec pjesame i izvodaca pisite velikim pocetnim slovom, a hashtagove malim//\n");
	printf("----------------------------------------\n");
}

void DodajuDatoteku(char song[], char artist[], char hashtags[])
{
	FILE* fp;
	fp = fopen("playlist.txt", "a");

	fputs(song, fp);

	fputs(artist, fp);

	fputs(hashtags, fp);

	fclose(fp);
}

bool DodajPjesmu(Song head)
{
	char song[MAX];
	char artist[MAX];
	char hashtags[MAX];
	char buff[5];

	printf("//Svaku rijec pjesame i izvodaca pisite velikim pocetnim slovom//\n");
	printf("//Hashtagove pisite bez razmaka//\n\n");

	fgets(buff, 5, stdin);
	printf("Unesite naziv pjesme: ");
	fgets(song, MAX, stdin);
	printf("Unesite ime izvodaca: ");
	fgets(artist, MAX, stdin);
	printf("Unesite hashtagove: ");
	fgets(hashtags, MAX, stdin);

	DodajNovi(head, song, artist, hashtags);
	DodajuDatoteku(song, artist, hashtags);

	return true;
}

void PretragaPoImenu(Song head, char buff[])
{
	int test = 0;
	if (head->next == NULL)
	{
		printf("Lista je prazna...\n");
		test = 2;
	}
	else
	{
		head = head->next;
		while (head != NULL)
		{
			if (!strcmp(head->song, buff))
			{
				printf("\nIme pjesme:\t%s", head->song);
				printf("Ime izvodaca:\t%s", head->artist);
				printf("Hashtags:\t%s\n\n", head->hashtags);
				if (test != 1)
					test = 1;
			}
			head = head->next;
		}
	}
	if (test == 0)
		printf("Takve pjeme nema u playlisti!\n");
}

void PretragaPoIzvodacu(Song head, char buff[])
{
	int test = 0;
	if (head->next == NULL)
	{
		printf("Lista je prazna...\n");
		test = 2;
	}
	else
	{
		head = head->next;
		while (head != NULL)
		{
			if (!strcmp(head->artist, buff))
			{
				printf("\nIme pjesme:\t%s", head->song);
				printf("Ime izvodaca:\t%s", head->artist);
				printf("Hashtags:\t%s\n\n", head->hashtags);
				if (test != 1)
					test = 1;
			}
			head = head->next;
		}
	}
	if (test == 0)
		printf("U listi ne postoji nijedna pjesma toga izvodaca!\n");
}

void PretragaPoHashtagu(Song head, char buff[])
{
	int test = 0;
	if (head->next == NULL)
	{
		printf("Lista je prazna...\n");
		test = 2;
	}
	else
	{
		head = head->next;
		while (head != NULL)
		{
			if (JeLiHashtag(head->hashtags, buff))
			{
				printf("\nIme pjesme:\t%s", head->song);
				printf("Ime izvodaca:\t%s", head->artist);
				printf("Hashtags:\t%s\n\n", head->hashtags);
				if (test != 1)
					test = 1;
			}
			head = head->next;
		}
	}
	if (test == 0)
		printf("U listi ne postoji nijedna pjesma s tim hashtagom!\n");
}

bool JeLiHashtag(char hashtags[], char hash[])
{
	char buff[MAX];
	int duljina = strlen(hashtags), i = 1, j = 0;

	if (hash[0] != '#')
	{
		while (hashtags[i] != '\n')
		{
			memset(buff, 0, sizeof(buff));
			while (hashtags[i] != '#' && hashtags[i] != '\n' && duljina >= i)
			{
				buff[j] = hashtags[i];
				j++;
				i++;
			}
			buff[j] = '\n';
			if (!strcmp(buff, hash))
				return true;
			j = 0;
			i++;
		}
		return false;
	}
	else
	{
		while (hashtags[i] != '\n')
		{
			memset(buff, 0, sizeof(buff));
			buff[0] = '#';
			j = 1;
			while (hashtags[i] != '#' && hashtags[i] != '\n' && duljina >= i)
			{
				buff[j] = hashtags[i];
				j++;
				i++;
			}
			buff[j] = '\n';
			if (!strcmp(buff, hash))
				return true;
			i++;
		}
		return false;
	}
}