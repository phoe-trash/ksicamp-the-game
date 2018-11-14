#include <string>
#include <cstdlib>
#include <iostream>
#include <string>

#include "../main.hpp"

const int8_t minigame_row = 3;
const int8_t minigame_col = 3;

void start(GameData& gameData) {
  std::cout << "Przechodzisz do tylnej strony budynku i widzisz "
            << (gameData.winda_repaired
                    ? "naprawioną przez siebę windę "
                    : "windę, która sprawia wrażenie niedziałającej")
            << std::endl;
}
/*
void draw_minigame(char k[][minigame_col+2], short off[minigame_col]) {
    std::cout << "Not yet implemented" << std::endl;
}
*/
void input_prompt(std::string& s) {
  std::cout << "> ";
  std::cin >> s;
}

bool lift_repairing_game(GameData& gameData) {  // TODO(seqre): Add minigame
  std::string choice;
  std::cout << "Po chwili dochodzisz do wniosku, że bez ściągnięcia"
            << "zewnętrznej osłony nic nie zdziałasz" << std::endl;
  if (gameData.inventory.find("śrubokręt") != gameData.inventory.end()) {
    std::cout
        << "Odkręcasz śrubki trzymające ochronną płytkę i ostrożnie ją ściągasz"
        << " podważając śrubokrętem" << std::endl
        << "Widzisz porwane kable bez izolacji, które czasami się stykając"
        << "tworzą efektowne zwarcia" << std::endl
        << "Co robisz?" << std::endl
        << "1. Naprawiam dalej" << std::endl
        << "2. Odpuszczam i przykręcam płytkę z powrotem" << std::endl;

    input_prompt(choice);
    if (choice[0] == '1') {
      std::cout << "Not implemented yet" << std::endl;
      /*
      std::cout << "Po chwili analizowania kabli stwierdzasz, że jak je
      poprzesuwasz i odpowiednio połączysz"
                << " to przyciski powinny zacząć działać" << std::endl;

      bool kable_poprawnie = false;
      bool ruch = false;

      char kable [minigame_row][minigame_col+2] {};
      short offset [minigame_col] {};

      while(kable_poprawnie) {
          while(!ruch) {
              clear_screen();
              draw_minigame(kable, offset);
          }

      }
      */
      return false;
    }
    return false;
  }
    std::cout << "Niestety, ale nie masz potrzebnego narzędzia do tego, wróć "
                 "później jak je zdobędziesz"
              << std::endl;
    return false;
}

Room choose_room(GameData& gameData, int8_t inside_idiot_counter) {
  std::string choice;
  while (true) {
    std::cout << "Co robisz?" << std::endl;
    wait_ms(200);
    std::cout << (gameData.winda_repaired
                      ? "1. Korzystam z windy i zjeżdżam na parter"
                      : "1. Podchodzę do windy, by zobaczyć czemu nie działa")
              << std::endl
              << "2. Idę do windy z przodu budynku" << std::endl
              << "3. Idę do biblioteki" << std::endl
              << "4. Idę do garażu (i robię przyps)" << std::endl
              << "5. Wracam na korytarz" << std::endl;

    if (!gameData.zaionc) {
      input_prompt(choice);
      if (choice[0] == '1') {
        if (!gameData.winda_repaired) {
          std::cout << "Widzisz, migotające co jakiś czas, podświetlenie "
                       "przycisku przywołania windy o jasnoniebieskim kolorze"
                    << std::endl
                    << "Po przyjrzeniu się zauważasz, że w środku musi być "
                       "jakieś zwarcie"
                    << std::endl
                    << std::endl
                    << "Co robisz?" << std::endl
                    << "1. Próbuję naprawić" << std::endl
                    << "2. Mam to w głęboko i próbuję użyć windy" << std::endl;

          do {
            input_prompt(choice);
            if (choice[0] == '1') {
              std::cout << "Not implemented yet" << std::endl;
              return WINDY_TYLNE;
              // if(lift_repairing_game(gameData)) gameData.winda_repaired =
              // true;
            }
            if (choice[0] == '2') {
              if (inside_idiot_counter == 8) {
                std::cout << "Przypominasz sobie o chińskich korzeniach i "
                             "stwierdzasz, że za 8 sprawdzeniem winda na pewno "
                             "będzie działać"
                          << std::endl;
                wait_ms(500);
                std::cout << "Naciskasz przycisk przywołania windy i w tym "
                             "momencie śmiertelnie razi Cię prąd"
                          << std::endl;
                wait_s(1);
                gameData.alive = false;
                return ZEWNATRZ;
              }

              std::cout << "Ślepy, czy głupi? Popsuta jest." << std::endl;
              wait_s(1);
              inside_idiot_counter++;
            } else {
              std::cout << "No debil no" << std::endl << std::endl;
            }
          } while (choice[0] != '1' && choice[0] != '2');
        } else {
          return WINDA_PARTER;
        }

      } else if (choice[0] == '2') {
        return WINDA_PIETRO;

      } else if (choice[0] == '3') {
        return BIBLIOTEKA;

      } else if (choice[0] == '4') {
        return GARAZ;

      } else if (choice[0] == '5') {
        return KORYTARZ;

      } else {  // TODO(seqre): Add waving "hand"
        std::cout << std::endl
                  << std::endl
                  << "To nie jest miejsce, którego szukasz" << std::endl
                  << "*Obi-Wan Kenobi's hand wave*" << std::endl
                  << "Wybierz raz jeszcze..." << std::endl
                  << "...tym razem mądrze, jeśli można." << std::endl
                  << std::endl;
      }
    } else {
      input_prompt(choice);
      unsigned seed1, seed2;
      if (choice[0] == '1') {
        if (!gameData.winda_repaired) {
          std::cout << "Jesteś debil, bo zamiast uciekać sprawdzasz windę"
                    << std::endl;
          gameData.alive = false;
          return ZEWNATRZ;
        }
        if (rand_r(&seed1) % 10 > 0) {
          std::cout << "Widzisz jak w ostatniej chwili drzwi od windy "
                       "zamykają się przed zaioncem"
                    << std::endl;
          return WINDA_PARTER;
        }
        std::cout << "Niestety, ale zaionc był szybszy od windy" << std::endl;
        gameData.alive = false;
        return ZEWNATRZ;
      }
      if (choice[0] == '2') {
        if (rand_r(&seed2) % 10 > 0) {
          std::cout << "Widzisz jak w ostatniej chwili drzwi od windy zamykają "
                       "się przed zaioncem"
                    << std::endl;
          return WINDA_PIETRO;
        }
        std::cout << "Niestety, ale zaionc był szybszy od windy" << std::endl;
        gameData.alive = false;
        return ZEWNATRZ;
      } else if (choice[0] == '3') {
        return BIBLIOTEKA;

      } else if (choice[0] == '4') {
        return GARAZ;

      } else if (choice[0] == '5') {
        return KORYTARZ;

      } else {
        std::cout << "Twoje niezdecydowanie działa na korzyść zaionca"
                  << std::endl;
        gameData.alive = false;
        return ZEWNATRZ;
      }
    }
  }
}

Room windyTylne(GameData& gameData) {
  start(gameData);

  int8_t idiot_counter = 0;

  return choose_room(gameData, idiot_counter);

  return KORYTARZ;
}