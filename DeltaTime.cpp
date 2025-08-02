void Setup::run()
{
    while (mIsActive)
    {
        SDL_Event event;
        SDL_GetMouseState(&mMousePos.x, &mMousePos.y);
        int32_t numKeys = 0;
        SDL_GetKeyboardState(&numKeys);
        mCircle.getStorageKeycodes().reserve(numKeys);
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    mIsActive = false;
                    break;
                }
            }

            if (event.type == SDL_EVENT_KEY_DOWN)
                mCircle.getStorageKeycodes()[event.key.key] = true;
            if (event.type == SDL_EVENT_KEY_UP)
                mCircle.getStorageKeycodes()[event.key.key] = false;
        }


        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mRenderer);
        SDL_SetRenderDrawColor(mRenderer, (uint8_t)(mBlocksColor[0] * 255),
                                          (uint8_t)(mBlocksColor[1] * 255),
                                          (uint8_t)(mBlocksColor[2] * 255),
                                          255);
        // getting time of the first frame
        float firstFrame = (float)SDL_GetTicks();

        mBlock.control(event);
        mBlock.update(mMousePos);
        mBlock.render(mRenderer, false);

        mUI.control(event, mIsActive, mBlocksColor, mCircleColor, mBlock, mCircle);
        mUI.render(mRenderer);
      
        SDL_RenderPresent(mRenderer);

        // setting the proper delay
        float deltaTime = (float)SDL_GetTicks() - firstFrame;
        // if deltaTime > 16 - then we will miss slowing our program down
        // if deltaTime < 16 - we will slow it down. Like 16 - deltatime
        // and we will get a desired number which can help slow our program down
        if (deltaTime < mDelay) // let it be 8 and 16
            SDL_Delay((Uint32)(mDelay - deltaTime)); // 16-8 = 8 
        // in order to make our fps properly, we need to slow down our program on 8 miliseconds 
        // with this equation we can do this 

        // multiplications for circle's speed
        float currentTime = (float)SDL_GetTicks(); // current time of the frame
        float deltaTime2 = currentTime - mDelay; // delta time from the last frame. usually it 16 fps which we set 
        mLastFrameRate = currentTime; // setting our frame as a last frame

        // cap delta time to prevent jumps
        const float MAX_DELTA_TIME = 50.0f;
        if (deltaTime2 > MAX_DELTA_TIME)
            deltaTime2 = MAX_DELTA_TIME;

        // convert to seconds and apply speed multiplier
        mCircle.setMultiplierSpeed(deltaTime2 * mUI.getTimeDoubler() * 0.001f);
    }
}
