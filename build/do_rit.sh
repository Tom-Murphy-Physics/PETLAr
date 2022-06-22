#!/bin/bash/

./PETLAr detr.mac
mv *.root R_data
cd ../analysis/
rm files_file.txt
ls ../build/R_data/ >> files_file.txt
root -b -q -l count_eR.c bg
mv *.root ./light_detection/R_data
ls light_detection/R_data >> file_list.txt
root -q -l write_R/write_det_sp.C
root -q -l write_R/write_edep.C
root -q -l write_R/write_enum.C
root -q -l write_R/write_numeion.C
root -q -l write_R/write_pen_depth.C
root -q -l write_R/write_size.C
root -q -l write_R/write_cloud.C
root -q -l write_R/write_2Dsp.C
root -q -l write_R/write_2Ddet_sp.C
rm -rf file_names_dir
mkdir file_names_dir
mv file*.txt file_names_dir
mv *.txt light_detection/R_data
cd light_detection/R_data
mkdir R_data_txt
mv *.txt R_data_txt
rm -rf ../R_data_txt
mv R_data_txt ..
cd ../R_data_c_files
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
cd ../../../build/

