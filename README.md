# Temperature-Monitoring-System
F431151

###IMPORTANT###

#Final Notebook found can be found in Test Branch#

##################################################

This project covers various topics related to programming and software engineering. Firstly, it teaches and assesses the use of github. The project tackles multiple areas including authentication issues and merge conflicts. Secondly, the project looks at Arduinos and the temperature sensor. Learning material is provided to support setup and answering questions. Task 3 is to build upon the provided code to monitor temperature and ultimately provide the results automatically into an excel csv file. Finally task 4 is to optimise the code, implementing adaptive sampling and potentially future variation trend prediction. 


Task 1.1 

This task is to research, test and explain why authentication issues arose in Google Colab. It looked into the issue of private repositories not being visible and the steps required to fix it. 

Task 1.2 

This task involved setting up a workflow to automate task management. The code was placed into a workflow that automatically confirmed when tasks 1.3 and 1.4 were completed. 

Task 1.3 

This task looked into why, under certain conditions, a branch can not be deleted. This was due to the user currently being on the branch it was trying to delete. When creating the new branch, it was automatically switched to.

Task 1.4

This task covered merge errors. As the same line of text had been edited on two separate branches, when the merge was triggered Github did not know what to do. The solution involved manually editing the texts to resolve the error. 

Task 2.1 

Research was required to answer the subsequent questions around Arduinos and temperature sensors.

Task 3.1

A function was created to detect the temperature sensor. This was printed into the output terminal every second due to the sampling rate. The system outputs readings to the Serial Monitor with a short delay. Data is collected over a 3 minute period. The data is stored in an array for future analysis. 

Task 3.2

A new function was created to apply the Discrete Fourier Transform (DFT) to convert temperature readings into the frequency domain. Frequency components and magnitudes are calculated using the provided equations. 

Task 3.3

A function called send_data_to_pc() is created to send all the data to the output terminal. Also the DFT magnitude spectrum needs to be computed. All the data is then sent to the computer in the format Time, Temperature, Frequency, Magnitude. The test duration was reduced to 2 minutes as nearly all the SRAM was in use. 

Task 3.4

All 3 power modes are defined and their conditions enable dynamic power mode selection. The results of the DFT were converted to average frequencies. This allowed the system to select the appropriate power mode based on defined conditions.

Task 3.5

Firstly, I had to change the void send_data_to_pc() function. I removed the spaces after the commas and removed the headers.
Next I had to set up excel. I enabled the data streamer and connected my arduino.
I had to go to advanced settings and change the data rows limit to 500 to allow for all my data to be displayed.
My 2 minute test recorded 120 data entries.
Finally I went into the settings sheet and set the data rows to 121. This allowed all the data and the power mode entry.

Task 3.6

The excel csv created in the previous code needed to be reformatted to simplify the coding. The python code then takes the data provided to plot both graphs. Issues arose with the file address, so a manual upload method was implemented. 

Task 4

Task 4 implemented optimisation by continuously monitoring 1 minute cycles. Memory usage was optimised by reducing from 120 seconds to 60 seconds. Output was changed to cycle summaries rather than all data. 


FILES


24WSA024_JNB_Arduino_Coursework_Final_2025S2(V1).ipynb

  Final coursework Notebook where project was complete

24WSA024_JNB_Coursework_Arduino_Programming_Beta_.ipynb

  Beta Notebook that was started but left for new notebook

Arduino Setup.jpg

  Shows setup of Arduino

Arduino_Code.ino

	Final code for task 4 in IDE format

project-notes.md

	Used for task 1.4

.github/workflows/task_verification.yml

	Workflow for task 1.2

threeminstemperature_f431151  CSV.csv

	Excel spreadsheet for outputed data in task 3.5

