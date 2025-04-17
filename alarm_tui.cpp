//#include <ncurses.h>
#include <ncursesw/ncurses.h>

#include <ctime>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <locale.h>

void wait_until(int hour, int minute) {
    while (true) {
        std::time_t now = std::time(nullptr);
        std::tm *local = std::localtime(&now);

        if (local->tm_hour == hour && local->tm_min == minute) break;

        // Pokazuje aktualny czas
        mvprintw(6, 2, "Aktualny czas: %02d:%02d:%02d  ", local->tm_hour, local->tm_min, local->tm_sec);
        refresh();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();

    int hour, minute;
    mvprintw(2, 2, "⏲️ Alarm - TUI wersja");
    mvprintw(4, 2, "Podaj godzinę alarmu (HH MM): ");
    scanw("%d %d", &hour, &minute);

    mvprintw(5, 2, "Ustawiono alarm na %02d:%02d", hour, minute);
    refresh();

    wait_until(hour, minute);

    clear();
    mvprintw(3, 2, "🔔 ALARM! 🔔");
    refresh();

    system("paplay /usr/share/sounds/freedesktop/stereo/alarm-clock-elapsed.oga");
    
    mvprintw(5, 2, "Naciśnij dowolny klawisz, aby zakończyć...");
    getch();

    endwin();
    return 0;
}
