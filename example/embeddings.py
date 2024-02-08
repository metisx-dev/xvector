import numpy as np
import requests
import json


# Function to fetch embeddings from the API
def fetch_embeddings(queries):
    response = requests.post(
        "https://api.sionic.ai/v2/embedding",
        headers={"Content-Type": "application/json"},
        data=json.dumps({"inputs": queries})
    )
    if response.status_code == 200:
        return response.json()
    else:
        raise Exception(f"API request failed with status code {response.status_code}")


def main():
    queries = [ # 여러분이 조회하고자 하시는 청크 단위의 값을 리스트 값으로 선언해주시기 바랍니다. 10개 이상의 샘플 값이 필요합니다.
        "Joseph Robinette Biden Jr is an American politician who is the 46th and current president of the United States",
        "Samuel Harris Altman is an American entrepreneur and investor best known as the CEO of OpenAI since 2019",
        "Taylor Alison Swift is an American singer-songwriter. Her songwriting, artistry, and entrepreneurship have influenced the music industry and popular culture.",
        "William Henry Gates III (born October 28, 1955) is an American businessman, investor, philanthropist, and writer best known for co-founding the software giant Microsoft",
        "Jen-Hsun Jensen Huang (Chinese: 黃仁勳; pinyin: Huáng Rénxūn; Pe̍h-ōe-jī: N̂g Jîn-hun; born February 17, 1963) is an American businessman, electrical engineer, and the co-founder, president and CEO of Nvidia Corporation.",
        "Lisa Su (simplified Chinese: 苏姿丰; traditional Chinese: 蘇姿丰; pinyin: Su Zifeng; Pe̍h-ōe-jī: So͘ Chu-hong; born 7 November 1969) is a Taiwanese-born American business executive and electrical engineer, who is the president, chief executive officer and chair of AMD.",
        "Elon Musk cofounded the electronic payment firm PayPal, and in 2002 he founded SpaceX, a company that makes rockets and spacecraft",
        "Barack Hussein Obama II is an American politician who served as the 44th president of the United States from 2009 to 2017.",
        "He is the founder, executive chairman, and former president and CEO of Amazon, the world's largest e-commerce and cloud computing company.",
        "Vitaly Dmitrievich Buterin, better known as Vitalik Buterin, is a Russian-Canadian computer programmer, and co-founder of Ethereum.",
        "This chapter defines the interface between the core Postgr",
        "eSQL system and index access methods,",
        " which manage individual index types. The core system know",
        "s nothing about indexes beyond what is specified here, ",
        " so it is possible to develop entirely new index types by ",
        "writing add-on code.",
        "All indexes in PostgreSQL are what are known technically a",
        "s secondary indexes; ",
        "that is, the index is physically separate from the table f",
        "ile that it describes. ",
        "Each index is stored as its own physical relation and so i",
        "s described by an entry in the pg_class catalog. ",
        "The contents of an index are entirely under the control of",
        " its index access method. ",
        "In practice, all index access methods divide indexes into ",
        "standard-size pages so that they can use the regular storage manager and buffer manager to access the index contents. ",
        "(All the existing index access methods furthermore use the",
        " standard page layout described in Section 73.6,",
        " and most use the same format for index tuple headers; but",
        " these decisions are not forced on an access method.)",
        "An index is effectively a mapping from some data key value",
        "s to tuple identifiers, or TIDs, of row versions (tuples) in the index's parent table.",
        " A TID consists of a block number and an item number withi",
        "n that block (see Section 73.6). ",
        " This is sufficient information to fetch a particular row ",
        "version from the table.",
        " Indexes are not directly aware that under MVCC, ",
        "fvcxzvas",
        " there might be multiple extant versions of the same logic",
        "al row; to an index, each tuple is an independent object that needs its own index entry. ",
        " Thus, an update of a row always creates all-new index ent",
        "ries for the row, even if the key values did not change. ",
        " (HOT tuples are an exception to this statement; but index",
        "es do not deal with those, either.)",
        " Index entries for dead tuples are reclaimed (by vacuuming",
        ") when the dead tuples themselves are reclaimed.",
        "Each index access method is described by a row in the pg_a",
        "m system catalog. ",
        "The pg_am entry specifies a name and a handler function fo",
        "r the index access method. ",
        "These entries can be created and deleted using the CREATE ",
        "ACCESS METHOD and DROP ACCESS METHOD SQL commands.",
        "An index access method handler function must be declared t",
        "o accept a single argument of type internal",
        "and to return the pseudo-type index_am_handler. The argum",
        "ent is a dummy value that simply serves ",
        "to prevent handler functions from being called directly f",
        "rom SQL commands. The result of the function must be a palloc'd struct of type IndexAmRoutine,",
        "which contains everything that the core code needs to kno",
        "w to make use of the index access method. The IndexAmRoutine struct, also called the access method's API struct, includes fields specifying assorted fixed properties of the access method, ",
        "such as whether it can support multicolumn indexes. More ",
        "importantly, it contains pointers to support functions for the access method, which do all of the real work to access indexes. ",
        "These support functions are plain C functions and are not",
        "visible or callable at the SQL level. The support functions are described in Section 64.2.",
        "The structure IndexAmRoutine is defined thus:",
        "To be useful, an index access method must also have one or",
        " more operator families and operator classes defined in pg_opfamily, pg_opclass, pg_amop, and pg_amproc. ",
        "These entries allow the planner to determine what kinds of",
        " query qualifications can be used with indexes of this access method. Operator families and classes are described in Section 38.16, which is prerequisite material for reading this chapter.",
        "An individual index is defined by a pg_class entry that de",
        "scribes it as a physical relation, plus a pg_index entry that shows the logical content of the index — ",
        "that is, the set of index columns it has and the semantics",
        " of those columns, as captured by the associated operator classes. The index columns (key values) can be either simple columns of the underlying table or expressions over the table rows.",
        " The index access method normally has no interest in where",
        " the index key values come from (it is always handed precomputed key values) but it will be very interested in the operator class information in pg_index. ",
        " Both of these catalog entries can be accessed as part of ",
        "the Relation data structure that is passed to all operations on the index.",
        "Some of the flag fields of IndexAmRoutine have nonobvious ",
        "implications. The requirements of amcanunique are discussed in Section 64.5. ",
        "The amcanmulticol flag asserts that the access method supp",
        "orts multi-key-column indexes, while amoptionalkey asserts that it allows scans where no indexable restriction clause is given for the first index column. When amcanmulticol is false",
        ", amoptionalkey essentially says whether the access method",
        " supports full-index scans without any restriction clause. Access methods that support multiple index columns must support scans that omit restrictions on any or all of the columns after the first; ",
        "however they are permitted to require some restriction to ",
        "appear for the first index column, and this is signaled by setting amoptionalkey false. One reason that an index AM might set amoptionalkey false is if it doesn't index null values. ",
        "Since most indexable operators are strict and hence cannot",
        " return true for null inputs, it is at first sight attractive to not store index entries for null values: they could never be returned by an index scan anyway. ",
        "However, this argument fails when an index scan has no res",
        "triction clause for a given index column. In practice this means that indexes that have amoptionalkey true must index nulls, since the planner might decide to use such an index with no scan keys at all.",
        " A related restriction is that an index access method that",
        " supports multiple index columns must support indexing null values in columns after the first, because the planner will assume the index can be used for queries that do not restrict these columns. ",
        " For example, consider an index on (a,b) and a query with ",
        "WHERE a = 4. The system will assume the index can be used to scan for rows with a = 4, which is wrong if the index omits rows where b is null. ",
        " It is, however, OK to omit rows where the first indexed c",
        "olumn is null. An index access method that does index nulls may also set amsearchnulls, indicating that it supports IS NULL and IS NOT NULL clauses as search conditions.",
        "The amcaninclude flag indicates whether the access method ",
        "supports “included” columns, that is it can store (without processing)",
        " additional columns beyond the key column(s). The requirem",
        "ents of the preceding paragraph apply only to the key columns. In particular, the combination of amcanmulticol=false and amcaninclude=true is sensible: it means that there can only be one key column,",
        " but there can also be included column(s). Also, included "
    ]

    # Fetch embeddings for the queries
    response_data = fetch_embeddings(queries)

    # Extract embeddings from the response
    embeddings = response_data['embedding'] if 'embedding' in response_data else []
    #print(f"embeddings=\n{embeddings}")

    # Convert embeddings to a numpy array
    a = np.array(embeddings)

    # Continue with your existing code
    b = np.linalg.norm(a, axis=1, keepdims=True)
    c = a / b
    #c = np.transpose(c).astype(np.float32).flatten()# 
    d = c.astype(np.float32).flatten()# 

    #print(f"c=\n{c}")
    #print(f"c.shape=\n{c.shape}")
    #print(f"c.dtype=\n{c.dtype}")

    #print(f"d=\n{d}")
    #print(f"d.shape=\n{d.shape}")
    #print(f"d.dtype=\n{d.dtype}")

    np.save(f"./{len(a)}-{len(a[0])}", d)


if __name__ == "__main__":
    main()

# [-0.00792217  0.02560848  0.00077758 ...  0.01267467  0.01262564
#  0.00918304]
# (30720,)
# float32