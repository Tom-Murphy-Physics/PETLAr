#!/bin/bash/

./PETLAr detz.mac
mv *.root Z_data
cd ../analysis/
rm files_file.txt
ls ../build/Z_data/ >> files_file.txt
root -b -q -l count_eZ.c bg
mv *.root ./light_detection/Z_data
ls light_detection/Z_data >> file_list.txt
root -q -l write_Z/write_det_sp.C
root -q -l write_Z/write_edep.C
root -q -l write_Z/write_enum.C
root -q -l write_Z/write_numeion.C
root -q -l write_Z/write_pen_depth.C
root -q -l write_Z/write_size.C
root -q -l write_Z/write_cloud.C
root -q -l write_Z/write_2Dsp.C
root -q -l write_Z/write_2Ddet_sp.C
rm -rf file_names_dir
mkdir file_names_dir
mv file*.txt file_names_dir
mv *.txt light_detection/Z_data
cd light_detection/Z_data
mkdir Z_data_txt
mv *.txt Z_data_txt
rm -rf ../Z_data_txt
mv Z_data_txt ..
cd ../Z_data_c_files
root -q -l plot_attach.C
root -q -l plot_chargepp.C
root -q -l plot_ed.C
root -q -l plot_enum.C
root -q -l plot_numeion.C
root -q -l plot_pen_depth.C
root -q -l plot_qpp.C
root -q -l plot_sp.C
root -q -l plot_detsp.C
root -q -l plot_cloud.C
root -q -l plot_ratio_attach.C
root -q -l plot_ratio_cloud.C
root -q -l plot_2Ddetsp.C
root -q -l plot_2Dsp.C
root -q -l plot_track_width2.C
cd ../../../build/

