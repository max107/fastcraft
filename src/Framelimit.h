//
// Created by max on 29.06.16.
//

#ifndef FASTCRAFT_FRAMELIMIT_H
#define FASTCRAFT_FRAMELIMIT_H

namespace fastcraft {

    class FpsManager {

    public:
        // The +0.00001 on max_frame_ticks is to offset the losses from rounding Otherwise we get 61/60 fps
        FpsManager(float fps_max) {
            max_frame_ticks = (1000.0 / fps_max) + 0.00001;
            frame_count = 0;
            last_second_ticks = SDL_GetTicks();
        }

        bool limit() {
            frame_count++;
            target_ticks = last_second_ticks + Uint32(frame_count * max_frame_ticks);
            current_ticks = SDL_GetTicks();

            average_ticks += current_ticks - last_frame_ticks;
            if (current_ticks - last_frame_ticks <= min_ticks) {
                min_ticks = current_ticks - last_frame_ticks;
            }
            if (current_ticks - last_frame_ticks >= max_frame_ticks) {
                max_ticks = current_ticks - last_frame_ticks;
            }

            if (current_ticks < target_ticks) {
                SDL_Delay(target_ticks - current_ticks);
                current_ticks = SDL_GetTicks();
            }

            last_frame_ticks = current_ticks;

            if (current_ticks - last_second_ticks >= 1000) {
                // Setup variables for read
                _fps = frame_count;
                _frame_average = average_ticks / frame_count;
                _frame_min = min_ticks;
                _frame_max = max_ticks;

                frame_count = 0;
                min_ticks = 1000;
                max_ticks = 0;
                average_ticks = 0;
                last_second_ticks = SDL_GetTicks();
                return true;
            }
            //--//
            return false;
        }

        Uint32 getFrameMin() {
            return _frame_min;
        }

        Uint32 getFrameMax() {
            return _frame_max;
        }

        double getFrameAverage() {
            return _frame_average;
        }

        int getFps() {
            return _fps;
        }

    protected:
        float max_frame_ticks;
        Uint32 last_second_ticks;
        int frame_count;
        //--//
        Uint32 min_ticks;
        Uint32 max_ticks;
        double average_ticks;
        Uint32 last_frame_ticks;
        //--//
        Uint32 current_ticks;
        Uint32 target_ticks;

    private:
        Uint32 _frame_min;
        Uint32 _frame_max;
        double _frame_average;
        int _fps;
    };

}

#endif //FASTCRAFT_FRAMELIMIT_H
