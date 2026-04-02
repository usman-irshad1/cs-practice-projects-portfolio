"""
Generate professional charts from metrics.csv for the Adaptive Traffic Simulator.
Produces 4 chart images in the project directory.
"""
import csv
import matplotlib
matplotlib.use('Agg')  # non-interactive backend
import matplotlib.pyplot as plt
import matplotlib.ticker as mticker
import os

CSV_PATH = r"c:\oops_folder\Project_DSA\metrics.csv"
OUT_DIR  = r"c:\oops_folder\Project_DSA"

# ── Read CSV ──
data = {}
with open(CSV_PATH, 'r') as f:
    reader = csv.DictReader(f)
    for col in reader.fieldnames:
        data[col] = []
    for row in reader:
        for col in reader.fieldnames:
            data[col].append(float(row[col]))

ticks = data['tick']

# ── Style Setup ──
plt.rcParams.update({
    'figure.facecolor': '#0d1117',
    'axes.facecolor': '#161b22',
    'axes.edgecolor': '#30363d',
    'axes.labelcolor': '#c9d1d9',
    'text.color': '#c9d1d9',
    'xtick.color': '#8b949e',
    'ytick.color': '#8b949e',
    'grid.color': '#21262d',
    'grid.linestyle': '--',
    'grid.alpha': 0.6,
    'font.family': 'sans-serif',
    'font.size': 11,
    'figure.dpi': 150,
})

COLORS = {
    'blue': '#58a6ff',
    'green': '#3fb950',
    'orange': '#d29922',
    'red': '#f85149',
    'purple': '#bc8cff',
    'cyan': '#39d2c0',
    'pink': '#f778ba',
    'gray': '#8b949e',
}

# ═══════════════════════════════════════════════════════════
# CHART 1: Travel Time Analysis (Cumulative, Windowed, Min, Max, P95)
# ═══════════════════════════════════════════════════════════
fig, ax = plt.subplots(figsize=(12, 6))

ax.fill_between(ticks, data['min_time'], data['max_time'], 
                alpha=0.15, color=COLORS['blue'], label='Min-Max Range')
ax.plot(ticks, data['cumulative_avg'], color=COLORS['blue'], linewidth=2.5, 
        marker='o', markersize=4, label='Cumulative Avg')
ax.plot(ticks, data['windowed_avg'], color=COLORS['cyan'], linewidth=2, 
        marker='s', markersize=3, linestyle='--', label='Windowed Avg (last 100)')
ax.plot(ticks, data['p95_time'], color=COLORS['orange'], linewidth=2, 
        marker='^', markersize=3, linestyle='-.', label='P95 Travel Time')
ax.plot(ticks, data['min_time'], color=COLORS['green'], linewidth=1, 
        alpha=0.7, label='Min Time')
ax.plot(ticks, data['max_time'], color=COLORS['red'], linewidth=1, 
        alpha=0.7, label='Max Time')

ax.set_xlabel('Simulation Tick', fontsize=12, fontweight='bold')
ax.set_ylabel('Travel Time (ticks)', fontsize=12, fontweight='bold')
ax.set_title('Travel Time Analysis Over Simulation', fontsize=16, fontweight='bold', 
             color='white', pad=15)
ax.legend(loc='upper left', fontsize=9, facecolor='#161b22', edgecolor='#30363d',
          labelcolor='#c9d1d9')
ax.grid(True)
plt.tight_layout()
plt.savefig(os.path.join(OUT_DIR, 'chart_travel_time.png'), bbox_inches='tight')
plt.close()
print("Chart 1: Travel Time Analysis - DONE")

# ═══════════════════════════════════════════════════════════
# CHART 2: Network Health (Rush Level + System Cost + Active Vehicles)
# ═══════════════════════════════════════════════════════════
fig, ax1 = plt.subplots(figsize=(12, 6))

# Rush level (left axis)
color_rush = COLORS['red']
ax1.fill_between(ticks, data['rush_level'], alpha=0.2, color=color_rush)
ax1.plot(ticks, data['rush_level'], color=color_rush, linewidth=2.5, 
         marker='o', markersize=4, label='Rush Level (Congestion)')
ax1.set_xlabel('Simulation Tick', fontsize=12, fontweight='bold')
ax1.set_ylabel('Rush Level (0 = empty, 1 = full)', fontsize=12, fontweight='bold',
               color=color_rush)
ax1.tick_params(axis='y', labelcolor=color_rush)
ax1.set_ylim(0, max(data['rush_level']) * 1.3)

# Active vehicles (right axis)
ax2 = ax1.twinx()
color_active = COLORS['cyan']
ax2.plot(ticks, data['active_vehicles'], color=color_active, linewidth=2, 
         marker='D', markersize=3, linestyle='--', label='Active Vehicles')
ax2.set_ylabel('Active Vehicles', fontsize=12, fontweight='bold', color=color_active)
ax2.tick_params(axis='y', labelcolor=color_active)

# System cost as bar chart (background)
ax3 = ax1.twinx()
ax3.spines['right'].set_position(('outward', 60))
color_cost = COLORS['orange']
ax3.bar(ticks, data['system_cost'], width=25, alpha=0.25, color=color_cost, label='System Cost')
ax3.set_ylabel('System Cost', fontsize=10, fontweight='bold', color=color_cost)
ax3.tick_params(axis='y', labelcolor=color_cost)

ax1.set_title('Network Health Dashboard', fontsize=16, fontweight='bold', 
              color='white', pad=15)

# Combined legend
lines1, labels1 = ax1.get_legend_handles_labels()
lines2, labels2 = ax2.get_legend_handles_labels()
lines3, labels3 = ax3.get_legend_handles_labels()
ax1.legend(lines1 + lines2 + lines3, labels1 + labels2 + labels3, 
           loc='upper right', fontsize=9, facecolor='#161b22', edgecolor='#30363d',
           labelcolor='#c9d1d9')
ax1.grid(True)
plt.tight_layout()
plt.savefig(os.path.join(OUT_DIR, 'chart_network_health.png'), bbox_inches='tight')
plt.close()
print("Chart 2: Network Health Dashboard - DONE")

# ═══════════════════════════════════════════════════════════
# CHART 3: Throughput & Arrivals
# ═══════════════════════════════════════════════════════════
fig, ax1 = plt.subplots(figsize=(12, 6))

# Arrived vehicles (bar)
ax1.bar(ticks, data['arrived'], width=30, color=COLORS['green'], alpha=0.5, label='Total Arrived')
ax1.set_xlabel('Simulation Tick', fontsize=12, fontweight='bold')
ax1.set_ylabel('Cumulative Arrivals', fontsize=12, fontweight='bold', color=COLORS['green'])
ax1.tick_params(axis='y', labelcolor=COLORS['green'])

# Throughput (line, right axis)
ax2 = ax1.twinx()
ax2.plot(ticks, data['throughput'], color=COLORS['purple'], linewidth=2.5, 
         marker='o', markersize=5, label='Throughput (v/tick)')
ax2.set_ylabel('Throughput (vehicles/tick)', fontsize=12, fontweight='bold',
               color=COLORS['purple'])
ax2.tick_params(axis='y', labelcolor=COLORS['purple'])

ax1.set_title('Vehicle Throughput & Completion Rate', fontsize=16, fontweight='bold',
              color='white', pad=15)

lines1, labels1 = ax1.get_legend_handles_labels()
lines2, labels2 = ax2.get_legend_handles_labels()
ax1.legend(lines1 + lines2, labels1 + labels2, 
           loc='center right', fontsize=10, facecolor='#161b22', edgecolor='#30363d',
           labelcolor='#c9d1d9')
ax1.grid(True)
plt.tight_layout()
plt.savefig(os.path.join(OUT_DIR, 'chart_throughput.png'), bbox_inches='tight')
plt.close()
print("Chart 3: Throughput & Arrivals - DONE")

# ═══════════════════════════════════════════════════════════
# CHART 4: Delay & Rerouting Analysis
# ═══════════════════════════════════════════════════════════
fig, ax1 = plt.subplots(figsize=(12, 6))

# Total delay
color_delay = COLORS['red']
ax1.fill_between(ticks, data['total_delay'], alpha=0.15, color=color_delay)
ax1.plot(ticks, data['total_delay'], color=color_delay, linewidth=2.5, 
         marker='o', markersize=4, label='Total Delay (ticks)')
ax1.set_xlabel('Simulation Tick', fontsize=12, fontweight='bold')
ax1.set_ylabel('Total Delay (ticks)', fontsize=12, fontweight='bold', color=color_delay)
ax1.tick_params(axis='y', labelcolor=color_delay)

# Reroutes (right axis)
ax2 = ax1.twinx()
color_reroute = COLORS['blue']
ax2.plot(ticks, data['reroutes'], color=color_reroute, linewidth=2, 
         marker='s', markersize=4, linestyle='--', label='Total Reroutes')
ax2.set_ylabel('Cumulative Reroutes', fontsize=12, fontweight='bold', color=color_reroute)
ax2.tick_params(axis='y', labelcolor=color_reroute)

ax1.set_title('Congestion Delay vs. Adaptive Rerouting', fontsize=16, fontweight='bold',
              color='white', pad=15)

lines1, labels1 = ax1.get_legend_handles_labels()
lines2, labels2 = ax2.get_legend_handles_labels()
ax1.legend(lines1 + lines2, labels1 + labels2, 
           loc='center right', fontsize=10, facecolor='#161b22', edgecolor='#30363d',
           labelcolor='#c9d1d9')
ax1.grid(True)
plt.tight_layout()
plt.savefig(os.path.join(OUT_DIR, 'chart_delay_rerouting.png'), bbox_inches='tight')
plt.close()
print("Chart 4: Delay & Rerouting - DONE")

print("\n=== ALL 4 CHARTS GENERATED ===")
print(f"Location: {OUT_DIR}")
