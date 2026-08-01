# Virtual Memory Simulator — Viva Function Report

## Project Architecture Overview

```
main() ──► Virtual_Memory_manager
               ├── Walker()            → FIFO simulation
               ├── Runner()            → LRU simulation
               └── SPRINTER_OPT_TLB() → OPT simulation
           Drawer (GUI versions)
               ├── Walker1()           → FIFO + Raylib GUI
               ├── Runner1()           → LRU + Raylib GUI
               └── SPRINTER_OPT_TLB1()→ OPT + Raylib GUI
```

---

## 1. `main()` — Entry Point
**File:** `OS_project.cpp`

```cpp
int main() {
    ofstream clear_csv("comparison_metrics.csv", ios::trunc);
    clear_csv << "Algorithm,TotalRequests,TLBHits,TLBMisses,HitRate,..."<< endl;
    clear_csv.close();

    Virtual_Memory_manager Sherlock;
    Sherlock.Walker();            // FIFO
    Sherlock.Runner();            // LRU
    Sherlock.SPRINTER_OPT_TLB(); // OPT

    Drawer Sherlock1;
    Sherlock1.Walker1();            // FIFO GUI
    Sherlock1.Runner1();            // LRU GUI
    Sherlock1.SPRINTER_OPT_TLB1(); // OPT GUI
}
```

**What it does:** Clears the CSV metrics file, runs all 3 algorithms in console mode, then runs them again with GUI visualization.

---

## 2. `FileConfiguration` — Config & Address Parser
**Files:** `FileConfiguration.h`, `FileConfiguration.cpp`

### Members
| Member | Type | Purpose |
|--------|------|---------|
| `physical_size` | `unsigned long long` | RAM size in bytes (e.g. 262144 = 256KB) |
| `page_size` | `unsigned long long` | Page size in bytes (e.g. 4096 = 4KB) |
| `TLB_size` | `unsigned long long` | Number of TLB entries (e.g. 16) |
| `virtual_size` | `unsigned long long` | Max virtual address space |
| `latency` | `unsigned long long` | RAM latency in nanoseconds |
| `actual_adress` | `vector<unsigned long long>` | Loaded hex addresses from file |

### Functions

#### `void FileParser()`
```cpp
config.FileParser();
```
Reads `Parameters.json` using the **jsoncpp** library. Parses `physical_size`, `page_size`, `TLB_size`, `virtual_size`, `latency` into the struct members.

**Key syntax:** Uses `Json::CharReaderBuilder` and `Json::parseFromStream()`.

#### `int No_of_bits_to_be_shifted()`
```cpp
int bits = config.No_of_bits_to_be_shifted();
```
Returns `ceil(log2(page_size))`. For 4KB pages → returns **12**. For 16B pages → returns **4**. Used to extract VPN from an address.

#### `unsigned long long getVirtual_page_number(unsigned long long address)`
```cpp
unsigned long long vpn = config.getVirtual_page_number(0x1A3F);
// 0x1A3F >> 12 = 1  (VPN = 1)
```
**Right-shifts** the address by `No_of_bits_to_be_shifted()` to extract the Virtual Page Number.

#### `unsigned long long offset(unsigned long long address)`
```cpp
unsigned long long off = config.offset(0x1A3F);
// 0x1A3F & 0xFFF = 0xA3F  (offset = 2623)
```
Uses **bitwise AND** with `(page_size - 1)` to extract the offset within the page.

#### `void Reading_Addresses()`
```cpp
config.Reading_Addresses();
```
Reads hex addresses from `addresses.txt` line-by-line using `infile >> hex >> address` and pushes them into `actual_adress` vector.

#### `void Display()`
```cpp
config.Display();
```
Prints all config values to console.

---

## 3. `Ram_memory` — Physical RAM Simulation
**Files:** `Ram_memory.h`, `Ram_memory.cpp`

### Constructor
```cpp
Ram_memory::Ram_memory(FileConfiguration& config)
```
Calculates `total_pages = physical_size / page_size` and creates a 2D vector `memory[total_pages][page_size]` initialized with `'-'`.

### Functions

#### `void write(unsigned long long physical, unsigned long long offset, char data)`
```cpp
mind_palace.write(frame_number, offset, 'W');
```
Writes a character into `memory[physical][offset]`.

#### `char read(unsigned long long physical, unsigned long long offset)`
```cpp
char c = mind_palace.read(frame_number, offset);
```
Returns the character stored at `memory[physical][offset]`.

---

## 4. `Page_frame_node` — Single Page Frame Entry
**File:** `Ram_memory.h`

```cpp
struct Page_frame_node {
    bool dirty_bit;            // true if page was written to
    bool valid_bit;            // true if page is valid
    unsigned long long physical_memory;  // frame number in RAM
};
```
Constructor sets `dirty_bit = false`, `valid_bit = true`.

---

## 5. `Value` — TLB Entry
**File:** `TLB_table.h`

```cpp
struct Value {
    unsigned long long physical_memory;  // mapped frame number
    bool valid_bit;                      // entry validity
};
```

---

## 6. `TLB` — Translation Lookaside Buffer
**Files:** `TLB_table.h`, `TLB_table.cpp`

### Key Data Structures
| Member | Type | Used By |
|--------|------|---------|
| `table` | `unordered_map<VPN, Value>` | All algorithms |
| `index_for_FIFO` | `list<VPN>` | FIFO eviction order |
| `LRU_queue` | `list<VPN>` | LRU recency order |
| `LRU_map` | `unordered_map<VPN, iterator>` | O(1) LRU access |
| `OPT_lookahead_buffer` | `vector<VPN>` | Future VPN sequence for OPT |

### Constructor
```cpp
TLB cache(config);  // cap = config.TLB_size, counters = 0
```

### Lookup Functions

#### `bool findFIFOTLB(vpn, &physical_memory_value)` — FIFO TLB Lookup
```cpp
bool found = cache.findFIFOTLB(vpn, frame_address);
```
Searches `table` for `vpn`. If found and valid → sets output, increments `tlb_hits`, returns `true`. Otherwise increments `tlb_misses`, returns `false`. **Does NOT reorder** (pure FIFO).

#### `bool find(vpn, &physical_memory_value)` — LRU TLB Lookup
```cpp
bool found = cache.find(vpn, frame_address);
```
Same as FIFO lookup but **also moves the VPN to the front of `LRU_queue`** on a hit (updating recency).

#### `bool findOPT_TLB(vpn, &physical_memory_value)` — OPT TLB Lookup
```cpp
bool found = cache.findOPT_TLB(vpn, frame_address);
```
Simple lookup — no reordering needed since OPT decides evictions by future distance, not past usage.

### Insertion Functions

#### `void Insert_with_FIFO_algo(vpn, frame, valid_bit)`
```cpp
cache.Insert_with_FIFO_algo(vpn, p_frame, true);
```
- If TLB has space → insert and push VPN to back of `index_for_FIFO`
- If full → **evict front of FIFO queue** (oldest entry), insert new one at back

#### `void insert_with_LRU_algo(vpn, frame, valid_bit)`
```cpp
cache.insert_with_LRU_algo(vpn, p_frame, true);
```
- If VPN exists → update and move to **front** of `LRU_queue`
- If space → insert at front
- If full → **evict back of LRU queue** (least recently used), insert new at front

#### `void insert_with_OPT_algo(vpn, frame, valid_bit, current_index)`
```cpp
cache.insert_with_OPT_algo(vpn, p_frame, true, index);
```
- If VPN exists → update
- If space → insert
- If full → scan `OPT_lookahead_buffer` from `current_index+1` forward. Find the VPN in TLB that is **used farthest in the future** (or never used again). Evict that victim.

#### `void OPT_LOOKAHEAD_INSERTION(config)`
```cpp
cache.OPT_LOOKAHEAD_INSERTION(config);
```
Pre-computes the full future VPN sequence from `config.actual_adress` and stores it in `OPT_lookahead_buffer`.

### Other Functions

#### `void TLB_Eviction(vpn)`
```cpp
l1.TLB_Eviction(evicted_vpn);
```
Called by Page_table when a page is evicted from RAM. Removes the VPN from TLB's `table`, `index_for_FIFO`, `LRU_queue`, and `LRU_map` to maintain consistency.

#### `void perfomance_metrics(latency, reads, writes, dirty_evictions, algo_name)`
```cpp
cache.perfomance_metrics(config.latency, pages.ram_read_count,
                         pages.ram_write_count, pages.dirty_evictions, "FIFO");
```
Calculates and prints:
- **Hit Rate** = `tlb_hits / request * 100`
- **EAT** = `(request×1 + misses×10 + reads×latency + writes×latency×2 + dirty×1000) / request`

Also appends a row to `comparison_metrics.csv`.

---

## 7. `Page_table` — Page Table / RAM Manager
**Files:** `Page_frame.h`, `Page_frame.cpp`

### Key Members
| Member | Purpose |
|--------|---------|
| `table` | `unordered_map<VPN, Page_frame_node>` — the page table |
| `FIFO_queue` | `list<VPN>` — FIFO eviction order for RAM |
| `LRU_queue` / `LRU_map` | LRU tracking for RAM frames |
| `lookahead_buffer` | Future VPN sequence for OPT RAM eviction |
| `mind_palace` | `Ram_memory` object — the actual RAM simulation |
| `frame_count` | How many frames currently allocated |
| `max_frames` | `physical_size / page_size` |
| `dirty_evictions`, `ram_read_count`, `ram_write_count` | Performance counters |

### Constructor
```cpp
Page_table pages(config);
// max_frames = physical_size / page_size
// frame_count = 0, all counters = 0
```

### Functions

#### `unsigned long long getPhysicalAddress(vpn, offset, for_writing, tlb, hit, w)` — LRU RAM
```cpp
unsigned long long frame = pages.getPhysicalAddress(vpn, offset, is_write, cache, x);
```
Three cases:
1. **VPN not in table + frames available** → allocate new frame, add to LRU queue
2. **VPN not in table + frames full** → evict LRU victim (back of queue). If dirty → write back to `HardDisk.txt`, increment `dirty_evictions`. Call `l1.TLB_Eviction()` to sync TLB.
3. **VPN already in table** → page table hit. Move to front of LRU queue. Update dirty bit if writing.

#### `unsigned long long acccess_using_FIFO(vpn, offset, for_writing, tlb, w)` — FIFO RAM
```cpp
unsigned long long frame = pages.acccess_using_FIFO(vpn, offset, is_write, cache, x);
```
Three cases:
1. **VPN in table** → page table hit, read/write RAM
2. **VPN not in table + frames available** → allocate, push to FIFO queue
3. **VPN not in table + frames full** → evict **front of FIFO queue**. If dirty → write to disk. Call `l1.TLB_Eviction()`.

#### `unsigned long long accessPageTableDirectly(vpn, offset, for_writing, w)`
```cpp
unsigned long long frame = pages.accessPageTableDirectly(vpn, offset, is_write, x);
// returns frame number if VPN exists, or (unsigned long long)-1 if not found
```
Quick page table check. Used by FIFO and OPT walkers — if returns `-1`, means page fault → must call `acccess_using_FIFO()` or `OPT_algorthim_for_getting_pshycal_number()`.

#### `unsigned long long OPT_algorthim_for_getting_pshycal_number(vpn, offset, for_writing, tlb, raw_addresses, index, w)` — OPT RAM
```cpp
unsigned long long frame = pages.OPT_algorthim_for_getting_pshycal_number(
    vpn, offset, is_write, cache, config.actual_adress, index, x);
```
If frames available → allocate. If full → scan `lookahead_buffer` from current `index` forward to find which VPN in table is used **farthest in future** (or never). Evict that victim. Logs eviction to `OPT_logging`.

#### `void LOOKAHEADINSERTION(config)`
```cpp
pages.LOOKAHEADINSERTION(config);
```
Pre-computes future VPN sequence for OPT RAM eviction (same idea as TLB's `OPT_LOOKAHEAD_INSERTION`).

#### `~Page_table()` — Destructor (Final Sync)
```cpp
// Called automatically when Page_table goes out of scope
```
Iterates all entries in `table`. Any page with `dirty_bit == true` gets its RAM content flushed to `HardDisk.txt`. Prints which VPN/frame pairs were dirty.

---

## 8. `Virtual_Memory_manager` — Simulation Orchestrators
**Files:** `Virtual_Memory_manager.h`, `Virtual_Memory_manager.cpp`

### `void Walker()` — FIFO Simulation
```cpp
Sherlock.Walker();
```
**Flow for each address:**
1. Parse address → extract `vpn` and `offset`
2. Determine Read/Write: `is_write = (instruction_count % 5 == 0)`
3. `cache.findFIFOTLB(vpn, frame_address)` → TLB lookup
4. If **TLB HIT** → `pages.accessPageTableDirectly()`
5. If **TLB MISS** → `pages.accessPageTableDirectly()` first
   - If returns `-1` (page fault) → `pages.acccess_using_FIFO()` loads from disk
   - Else → page table hit
6. `cache.Insert_with_FIFO_algo()` → insert into TLB
7. Log to `FIFO_logging.txt`

### `void Runner()` — LRU Simulation
```cpp
Sherlock.Runner();
```
**Flow for each address:**
1. Same address parsing and R/W determination
2. `cache.find(vpn, frame_address)` → LRU TLB lookup (reorders on hit)
3. If **TLB HIT** → `pages.getPhysicalAddress(... hit=true)` updates RAM LRU
4. If **TLB MISS** → `pages.getPhysicalAddress(... hit=false)` handles page fault with LRU eviction
5. `cache.insert_with_LRU_algo()` → insert into TLB
6. Log to `log.txt`

### `void SPRINTER_OPT_TLB()` — Full OPT Simulation
```cpp
Sherlock.SPRINTER_OPT_TLB();
```
**Flow for each address:**
1. **Pre-computation:** `cache.OPT_LOOKAHEAD_INSERTION(config)` + `pages.LOOKAHEADINSERTION(config)` → build lookahead buffers for both TLB and RAM
2. Same address parsing
3. `cache.findOPT_TLB(vpn, frame_address)` → OPT TLB lookup
4. If **TLB HIT** → `pages.accessPageTableDirectly()`
5. If **TLB MISS** → `pages.accessPageTableDirectly()` first
   - If `-1` → `pages.OPT_algorthim_for_getting_pshycal_number()` (OPT eviction for RAM)
6. `cache.insert_with_OPT_algo(vpn, frame, true, index)` → OPT eviction for TLB
7. Log to `OPT_logging`

---

## 9. `Drawer` — GUI Visualization Versions
**Files:** `Drawer.h`, `Drawer.cpp`

Same logic as `Virtual_Memory_manager` but adds **Raylib GUI rendering** after each address access.

#### `void Walker1()` — FIFO with GUI
#### `void Runner1()` — LRU with GUI
#### `void SPRINTER_OPT_TLB1()` — OPT with GUI

Each creates a `MemoryVisualizer gui(1200, 800)` and calls `gui.Render()` every iteration inside a `while (gui.IsRunning())` loop.

---

## 10. `MemoryVisualizer` — Raylib GUI Renderer
**File:** `mem_visualization.h`

```cpp
MemoryVisualizer gui(1200, 800);
```

### `void Render(TLB&, Page_table&, bool hit, FileConfiguration&, int activeIndex, string algoName)`
Draws three panels:
- **Left Panel:** Config values + live metrics (hits, misses, reads, dirty evictions)
- **Center Panel:** TLB slots — GREEN = hit, RED = miss, BLACK = eviction
- **Right Panel:** RAM frame grid — GREEN = clean, RED = dirty, BLACK = evicted, GRAY = empty

---

## Complete Call Chain Summary

```
main()
 ├── Walker() [FIFO]
 │    ├── config.FileParser()          → reads Parameters.json
 │    ├── config.Reading_Addresses()   → reads addresses.txt
 │    ├── For each address:
 │    │    ├── config.getVirtual_page_number(addr)  → VPN
 │    │    ├── config.offset(addr)                  → offset
 │    │    ├── cache.findFIFOTLB(vpn, &frame)       → TLB lookup
 │    │    ├── pages.accessPageTableDirectly(...)    → quick PT check
 │    │    ├── pages.acccess_using_FIFO(...)         → FIFO page fault handler
 │    │    └── cache.Insert_with_FIFO_algo(...)      → TLB insert
 │    └── cache.perfomance_metrics(...)              → print + CSV
 │
 ├── Runner() [LRU]
 │    ├── (same setup)
 │    ├── For each address:
 │    │    ├── cache.find(vpn, &frame)               → LRU TLB lookup
 │    │    ├── pages.getPhysicalAddress(...)          → LRU page handler
 │    │    └── cache.insert_with_LRU_algo(...)        → TLB insert
 │    └── cache.perfomance_metrics(...)
 │
 └── SPRINTER_OPT_TLB() [OPT]
      ├── cache.OPT_LOOKAHEAD_INSERTION(config)      → TLB lookahead
      ├── pages.LOOKAHEADINSERTION(config)            → RAM lookahead
      ├── For each address:
      │    ├── cache.findOPT_TLB(vpn, &frame)         → OPT TLB lookup
      │    ├── pages.accessPageTableDirectly(...)
      │    ├── pages.OPT_algorthim_for_getting_pshycal_number(...)  → OPT eviction
      │    └── cache.insert_with_OPT_algo(...)         → OPT TLB insert
      └── cache.perfomance_metrics(...)
```

---

## Key Data Structures Used

| Structure | C++ Type | Purpose |
|-----------|----------|---------|
| TLB table | `unordered_map<VPN, Value>` | O(1) VPN→frame lookup |
| FIFO queue | `list<VPN>` | Tracks insertion order |
| LRU queue | `list<VPN>` | Most-recent at front, least-recent at back |
| LRU map | `unordered_map<VPN, list::iterator>` | O(1) access to any node in LRU list |
| Page table | `unordered_map<VPN, Page_frame_node>` | VPN→frame+dirty+valid mapping |
| RAM | `vector<vector<char>>` | 2D array simulating physical memory |
| Lookahead | `vector<VPN>` | Pre-computed future VPN sequence for OPT |

---

## Key Formulas

**VPN extraction:**
```
VPN = address >> ceil(log2(page_size))
```

**Offset extraction:**
```
offset = address & (page_size - 1)
```

**EAT calculation:**
```
EAT = (requests×1ns + misses×10ns + reads×latency + writes×2×latency + dirty_evictions×1000ns) / requests
```

**Write detection:**
```
is_write = (instruction_count % 5 == 0)   // every 5th instruction is a write
```
