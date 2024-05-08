#!/bin/sh

experiment() {
    options="$1"
    output="$2"

    for file in ./instances/*150
    do

        ./lop $options -i $file >> $output
    done
}

experiments() {
    # experiment "--ii --random --transpose --first" ./statistics/experiments/ii_random_transpose_first.txt
    # experiment "--ii --random --exchange --first" ./statistics/experiments/ii_random_exchange_first.txt
    # experiment "--ii --random --insert --first" ./statistics/experiments/ii_random_insert_first.txt

    # experiment "--ii --random --transpose --best " ./statistics/experiments/ii_random_transpose_best.txt
    # experiment "--ii --random --exchange --best" ./statistics/experiments/ii_random_exchange_best.txt
    # experiment "--ii --random --insert --best" ./statistics/experiments/ii_random_insert_best.txt

    # experiment "--ii --cw --transpose  --first" ./statistics/experiments/ii_cw_transpose_first.txt
    # experiment "--ii --cw --exchange --first" ./statistics/experiments/ii_cw_exchange_first.txt
    # experiment "--ii --cw --insert --first" ./statistics/experiments/ii_cw_insert_first.txt

    # experiment "--ii --cw --transpose --best" ./statistics/experiments/ii_cw_transpose_best.txt
    # experiment "--ii --cw --exchange --best" ./statistics/experiments/ii_cw_exchange_best.txt
    # experiment "--ii --cw --insert --best " ./statistics/experiments/ii_cw_insert_best.txt

    # experiment "--vnd --cw --transpose-exchange-insert --first" ./statistics/experiments/vnd_cw_transpose-exchange-insert_first.txt
    # experiment "--vnd --cw --transpose-insert-exchange --first " ./statistics/experiments/vnd_cw_transpose-insert-exchange_first.txt

    experiment "--sa --cw --insert --first" ./statistics/experiments/sa_random_insert_first.txt
    
    experiment "--ils --cw --insert --first" ./statistics/experiments/ils_cw_insert_first.txt



}


report() {
    input_file="$1"
    output_file="$2"

    filename=$(basename "$input_file" .txt)
    awk -v filename="$filename" '{sum1 += $4; sum2 += $5; count++} END {printf "%s %f %f\n", filename, (count > 0) ? sum1 / count : 0, sum2}' "$input_file" >> "$output_file"
}


reports() {
    for file in ./statistics/experiments/*.txt
    do
        report "$file" "./statistics/reports/report.txt"
    done

}

compute_average() {
    if [ ! -f "./statistics/reports/max_runtime.txt" ]; then
        echo "Computing max runtime..."
        instances_dir="./instances"
        statistics_dir="./statistics"
        experiments_dir="${statistics_dir}/experiments"
        filename1="vnd_cw_transpose-exchange-insert_first.txt"
        filename2="vnd_cw_transpose-insert-exchange_first.txt"

        mkdir -p statistics/reports
        > ./statistics/reports/max_runtime.txt

        for instance in ${instances_dir}/*150
        do
            instance_name=$(basename "$instance")
            max_runtime=0
            while read -r line1 && read -r line2 <&3; do
                columns1=($line1)
                columns2=($line2)
                if [ "${columns1[0]}" = "${columns2[0]}" ] && [ "${columns1[0]}" = "${instance_name}" ]; then
                    runtime1=${columns1[4]}
                    runtime2=${columns2[4]}
                    echo $runtime1
                    echo $runtime2
                    max_runtime=$(python -c "print(format((($runtime1 + $runtime2)*100 / 2), '.3f'))")
                    echo "${instance_name} ${max_runtime}" >> ./statistics/reports/max_runtime.txt
                    break
                fi
            done <"${experiments_dir}/${filename1}" 3<"${experiments_dir}/${filename2}"
        done
    else
        echo "Max runtime already computed."
    fi
}

statistical_tests() {
    "C:\\Program Files\\R\\R-4.0.3\\bin\\Rscript" ./statistical_tests.r
}

experiments
reports
# compute_average
# statistical_tests