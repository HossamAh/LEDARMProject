## LED ARM project

# Project describtion
project to control led on/off period with 2 switches

# Hardware
*   tivac 
*   LED
*   2 switches

# Drivers in projects:
* GPIO
* NVIC
* SysTick
* GPT
* System clock


**All drivers implemented from scratch**

# Operation:
- starting from idle state when the confirm button is clicked, configuration of on time state is started.
- in configure on time state increment button increases the on time by 1 second, to exit from this state confirm button click is required.
- in configure off time state increment button increases the off time by 1 second, to exit from this state confirm button click is required.
- after on/off configuration on state is started then off state.
- after on and off periods led is started again with the same configuration, To start new configuration cycle confirm button is required to switch system to configuration state again.
