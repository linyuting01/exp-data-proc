## log of expt preprocess in smd-16-1.


### pokec

1. using `pokec_gen_nodes` to generate nodes file **pokec.v** with origin edge file **pokec.e**.
2. using `gpmetis_ve` to partition graph into _k_ part.
3. using `pokec_gen_partitions` to prefetch nodes and generate partitions with edges.
3. using `pokec_fulfil_partitions` to add property nodes into partitions.

----------------------------------------------------------

### yagos3

1. download **yagoFacts.tsv**;
2. manually assign node type in edge pattern, store in file **vlabel**
3. using `yago2_map2int` convert graph to numeric graph **yago2.e**, adding node type and recording string-int mapping.
4. 