"""
Convert function_report.md to a professional PDF.
Uses fpdf2 with its write_html() for table + formatting support.
"""
import re
from fpdf import FPDF
import markdown

INPUT  = r"C:\Users\usman\.gemini\antigravity\brain\f92b16aa-a869-4a7b-a5f3-d2d5568d7a8b\artifacts\function_report.md"
OUTPUT = r"c:\oops_folder\Project_DSA\Function_Report.pdf"

# ── Read the markdown ──
with open(INPUT, "r", encoding="utf-8") as f:
    md_text = f.read()

# ── Pre-process: remove mermaid blocks ──
md_text = re.sub(
    r'```mermaid.*?```',
    '> **[Diagram]** See the original .md file for the interactive Mermaid call-graph diagram.',
    md_text, flags=re.DOTALL
)

# ── Pre-process: convert alert blocks to blockquotes ──
for key, icon in [('NOTE','[i]'), ('TIP','[TIP]'), ('IMPORTANT','[!]'), ('WARNING','[!]'), ('CAUTION','[!!]')]:
    pattern = rf'>\s*\[!{key}\]\s*\n((?:>.*\n?)*)'
    def repl(m, icon=icon, key=key):
        body = re.sub(r'^>\s?', '', m.group(1), flags=re.MULTILINE).strip()
        return f'> **{icon} {key}:** {body}\n'
    md_text = re.sub(pattern, repl, md_text)

# ── Convert markdown to HTML ──
html_body = markdown.markdown(md_text, extensions=["tables", "fenced_code", "sane_lists"])

# ── Fix some HTML for fpdf2 compatibility ──
# fpdf2's write_html doesn't support <pre><code> well, so convert to styled blocks
html_body = html_body.replace('<pre><code>', '<pre style="font-family: Courier; font-size: 8pt; background-color: #f0f0f0;">')
html_body = html_body.replace('</code></pre>', '</pre>')
# Remove standalone <code> styling issues
html_body = re.sub(r'<code>(.*?)</code>', r'<font face="Courier" size="8">\1</font>', html_body)

# ── Build PDF ──
class PDF(FPDF):
    def header(self):
        if self.page_no() == 1:
            return
        self.set_font("Helvetica", "I", 8)
        self.set_text_color(150, 150, 150)
        self.cell(0, 5, "Function Report - Adaptive Traffic Simulator", align="C")
        self.ln(8)
        self.set_draw_color(200, 200, 200)
        self.line(10, self.get_y(), self.w - 10, self.get_y())
        self.ln(3)

    def footer(self):
        self.set_y(-15)
        self.set_font("Helvetica", "I", 8)
        self.set_text_color(150, 150, 150)
        self.cell(0, 10, f"Page {self.page_no()}/{{nb}}", align="C")

pdf = PDF(orientation='P', unit='mm', format='A4')
pdf.alias_nb_pages()
pdf.set_auto_page_break(auto=True, margin=20)
pdf.add_page()

# ── Cover / Title ──
pdf.ln(40)
pdf.set_font("Helvetica", "B", 28)
pdf.set_text_color(15, 52, 96)
pdf.cell(0, 15, "Function Report", align="C", new_x="LMARGIN", new_y="NEXT")
pdf.ln(3)
pdf.set_font("Helvetica", "", 14)
pdf.set_text_color(80, 80, 80)
pdf.cell(0, 10, "Adaptive Traffic Simulator with", align="C", new_x="LMARGIN", new_y="NEXT")
pdf.cell(0, 10, "Dynamic Rerouting & Signal Control", align="C", new_x="LMARGIN", new_y="NEXT")
pdf.ln(10)
pdf.set_draw_color(15, 52, 96)
pdf.set_line_width(0.8)
pdf.line(60, pdf.get_y(), pdf.w - 60, pdf.get_y())
pdf.ln(10)
pdf.set_font("Helvetica", "I", 11)
pdf.set_text_color(120, 120, 120)
pdf.cell(0, 8, "Every function in the project, what it does, and who calls it.", align="C", new_x="LMARGIN", new_y="NEXT")
pdf.ln(30)
pdf.set_font("Helvetica", "", 10)
pdf.set_text_color(100, 100, 100)
pdf.cell(0, 6, "Project: Adaptive Traffic Simulator", align="C", new_x="LMARGIN", new_y="NEXT")
pdf.cell(0, 6, "Language: C++ (with Raylib visualization)", align="C", new_x="LMARGIN", new_y="NEXT")

# ── Content pages ──
pdf.add_page()
pdf.set_text_color(0, 0, 0)

# Since write_html has limits, let's parse the markdown more carefully 
# and build the PDF section by section.

lines = md_text.split('\n')
i = 0
in_code_block = False
code_buffer = []
in_table = False
table_rows = []

def flush_table(pdf, rows):
    if not rows:
        return
    # Calculate column count from first row
    cols = len(rows[0])
    if cols == 0:
        return
    usable = pdf.w - 20  # margins
    col_w = usable / cols
    # Limit col widths for readability
    if cols <= 3:
        col_w = usable / cols
    elif cols <= 4:
        col_w = usable / cols
    else:
        col_w = usable / cols

    # Header row
    pdf.set_font("Helvetica", "B", 8)
    pdf.set_fill_color(15, 52, 96)
    pdf.set_text_color(255, 255, 255)
    for j, cell_text in enumerate(rows[0]):
        pdf.cell(col_w, 6, cell_text.strip(), border=1, fill=True, align="C")
    pdf.ln()

    # Data rows
    pdf.set_font("Helvetica", "", 7.5)
    pdf.set_text_color(30, 30, 30)
    for ri, row in enumerate(rows[1:]):
        if ri % 2 == 0:
            pdf.set_fill_color(248, 249, 250)
        else:
            pdf.set_fill_color(255, 255, 255)
        
        # Calculate max height needed
        max_lines = 1
        for cell_text in row:
            text_w = pdf.get_string_width(cell_text.strip()) + 2
            if text_w > col_w:
                max_lines = max(max_lines, int(text_w / col_w) + 1)
        
        row_h = 5 * max_lines
        
        # Check page break
        if pdf.get_y() + row_h > pdf.h - 25:
            pdf.add_page()
            # Reprint header
            pdf.set_font("Helvetica", "B", 8)
            pdf.set_fill_color(15, 52, 96)
            pdf.set_text_color(255, 255, 255)
            for cell_text in rows[0]:
                pdf.cell(col_w, 6, cell_text.strip(), border=1, fill=True, align="C")
            pdf.ln()
            pdf.set_font("Helvetica", "", 7.5)
            pdf.set_text_color(30, 30, 30)
        
        x_start = pdf.get_x()
        y_start = pdf.get_y()
        
        for j, cell_text in enumerate(row):
            x = x_start + j * col_w
            pdf.set_xy(x, y_start)
            if ri % 2 == 0:
                pdf.set_fill_color(248, 249, 250)
            else:
                pdf.set_fill_color(255, 255, 255)
            # Draw cell background
            pdf.rect(x, y_start, col_w, row_h, style='DF')
            pdf.set_xy(x + 1, y_start + 1)
            pdf.multi_cell(col_w - 2, 4, cell_text.strip(), border=0)
        
        pdf.set_xy(x_start, y_start + row_h)
    pdf.ln(3)

def sanitize_latin1(text):
    """Replace non-latin1 chars so fpdf2 Helvetica/Courier can render them."""
    replacements = {
        '\U0001f50d': '', '\u2b50': '*', '\u2705': '[OK]',
        '\u26a0': '[!]', '\ufe0f': '', '\u2139': '[i]',
        '\U0001f4a1': '[TIP]', '\U0001f534': '[!]',
        '\U0001f4ca': '[Chart]', '\U0001f4cb': '[List]',
        '\u2192': '->', '\u2190': '<-', '\u2194': '<->',
        '\u2022': '-', '\u2013': '-', '\u2014': '--',
        '\u2018': "'", '\u2019': "'", '\u201c': '"', '\u201d': '"',
        '\u2026': '...', '\u00d7': 'x', '\u2265': '>=', '\u2264': '<=',
        '\u2260': '!=', '\u2248': '~=', '\u03b1': 'alpha', '\u03b2': 'beta',
        '\u2211': 'Sum', '\u221a': 'sqrt', '\u221e': 'inf', '\u2212': '-',
    }
    for k, v in replacements.items():
        text = text.replace(k, v)
    return text.encode('latin-1', errors='replace').decode('latin-1')

def clean_md(text):
    """Remove markdown formatting and non-latin1 chars for plain text output."""
    text = re.sub(r'\*\*(.+?)\*\*', r'\1', text)  # bold
    text = re.sub(r'\*(.+?)\*', r'\1', text)  # italic
    text = re.sub(r'`(.+?)`', r'\1', text)  # inline code
    text = re.sub(r'\[(.+?)\]\(.*?\)', r'\1', text)  # links
    return sanitize_latin1(text)

while i < len(lines):
    line = lines[i]
    
    # Code blocks
    if line.strip().startswith('```') and not in_code_block:
        in_code_block = True
        code_buffer = []
        i += 1
        continue
    elif line.strip().startswith('```') and in_code_block:
        in_code_block = False
        # Print code block
        if pdf.get_y() > pdf.h - 40:
            pdf.add_page()
        pdf.set_fill_color(240, 242, 245)
        pdf.set_font("Courier", "", 7.5)
        pdf.set_text_color(50, 50, 50)
        code_text = '\n'.join(code_buffer)
        x = pdf.get_x()
        y = pdf.get_y()
        # Draw background
        code_lines_count = len(code_buffer)
        block_h = code_lines_count * 4 + 6
        if y + block_h > pdf.h - 25:
            pdf.add_page()
            y = pdf.get_y()
        pdf.rect(10, y, pdf.w - 20, block_h, style='F')
        pdf.set_xy(12, y + 2)
        for cl in code_buffer:
            pdf.cell(0, 4, sanitize_latin1(cl), new_x="LMARGIN", new_y="NEXT")
            pdf.set_x(12)
        pdf.ln(4)
        pdf.set_text_color(0, 0, 0)
        code_buffer = []
        i += 1
        continue
    elif in_code_block:
        code_buffer.append(line)
        i += 1
        continue
    
    # Tables
    if '|' in line and line.strip().startswith('|'):
        cells = [c.strip() for c in line.strip().strip('|').split('|')]
        # Skip separator rows (----)
        if all(re.match(r'^[-:]+$', c) for c in cells):
            i += 1
            continue
        cells = [clean_md(c) for c in cells]
        table_rows.append(cells)
        # Check if next line is not a table row
        if i + 1 >= len(lines) or not lines[i+1].strip().startswith('|'):
            flush_table(pdf, table_rows)
            table_rows = []
        i += 1
        continue
    
    # Headings
    clean_line = clean_md(line)
    
    if line.startswith('# ') and not line.startswith('##'):
        if pdf.get_y() > 40:
            pdf.add_page()
        pdf.set_font("Helvetica", "B", 18)
        pdf.set_text_color(15, 52, 96)
        pdf.cell(0, 12, clean_line[2:].strip(), new_x="LMARGIN", new_y="NEXT")
        pdf.set_draw_color(15, 52, 96)
        pdf.set_line_width(0.5)
        pdf.line(10, pdf.get_y(), pdf.w - 10, pdf.get_y())
        pdf.ln(4)
        i += 1
        continue
    
    if line.startswith('## '):
        pdf.ln(3)
        if pdf.get_y() > pdf.h - 35:
            pdf.add_page()
        pdf.set_font("Helvetica", "B", 14)
        pdf.set_text_color(22, 83, 126)
        pdf.cell(0, 10, clean_line[3:].strip(), new_x="LMARGIN", new_y="NEXT")
        pdf.set_draw_color(220, 220, 220)
        pdf.set_line_width(0.3)
        pdf.line(10, pdf.get_y(), pdf.w - 10, pdf.get_y())
        pdf.ln(3)
        i += 1
        continue
    
    if line.startswith('### '):
        pdf.ln(2)
        if pdf.get_y() > pdf.h - 30:
            pdf.add_page()
        pdf.set_font("Helvetica", "B", 12)
        pdf.set_text_color(26, 109, 62)
        pdf.cell(0, 8, clean_line[4:].strip(), new_x="LMARGIN", new_y="NEXT")
        pdf.ln(2)
        i += 1
        continue

    if line.startswith('#### '):
        pdf.ln(1)
        if pdf.get_y() > pdf.h - 25:
            pdf.add_page()
        pdf.set_font("Helvetica", "B", 10)
        pdf.set_text_color(50, 50, 50)
        text = clean_line[5:].strip()
        pdf.cell(0, 7, text, new_x="LMARGIN", new_y="NEXT")
        pdf.ln(1)
        i += 1
        continue
    
    if line.startswith('##### '):
        pdf.ln(1)
        if pdf.get_y() > pdf.h - 25:
            pdf.add_page()
        pdf.set_font("Helvetica", "BI", 9.5)
        pdf.set_text_color(80, 80, 80)
        pdf.cell(0, 6, clean_line[6:].strip(), new_x="LMARGIN", new_y="NEXT")
        pdf.ln(1)
        i += 1
        continue
    
    # Horizontal rules
    if line.strip() == '---' or line.strip() == '***':
        pdf.set_draw_color(200, 200, 200)
        pdf.set_line_width(0.2)
        pdf.line(10, pdf.get_y() + 2, pdf.w - 10, pdf.get_y() + 2)
        pdf.ln(5)
        i += 1
        continue
    
    # Blockquotes / alerts
    if line.startswith('> '):
        quote_text = clean_md(line[2:].strip())
        if pdf.get_y() > pdf.h - 25:
            pdf.add_page()
        pdf.set_fill_color(240, 244, 255)
        pdf.set_draw_color(15, 52, 96)
        y = pdf.get_y()
        pdf.set_font("Helvetica", "I", 9)
        pdf.set_text_color(60, 60, 80)
        # Calculate height
        text_w = pdf.w - 30
        pdf.set_x(18)
        pdf.multi_cell(text_w, 5, quote_text)
        y2 = pdf.get_y()
        # Draw left border
        pdf.set_line_width(1)
        pdf.line(12, y, 12, y2)
        pdf.ln(2)
        pdf.set_text_color(0, 0, 0)
        i += 1
        continue
    
    # Bullet points
    if line.strip().startswith('- ') or line.strip().startswith('* '):
        indent = min(len(line) - len(line.lstrip()), 20)
        bullet_text = clean_md(line.strip()[2:])
        pdf.set_font("Helvetica", "", 9)
        pdf.set_text_color(30, 30, 30)
        pdf.set_x(12 + indent)
        pdf.cell(4, 5, '-')
        w = max(pdf.w - 28 - indent, 40)
        pdf.multi_cell(w, 5, bullet_text)
        i += 1
        continue
    
    # Numbered list
    m = re.match(r'^(\s*)(\d+)\.\s+(.+)', line)
    if m:
        indent = min(len(m.group(1)), 20)
        num = m.group(2)
        text = clean_md(m.group(3))
        pdf.set_font("Helvetica", "", 9)
        pdf.set_text_color(30, 30, 30)
        pdf.set_x(12 + indent)
        pdf.cell(6, 5, f"{num}.")
        w = max(pdf.w - 30 - indent, 40)
        pdf.multi_cell(w, 5, text)
        i += 1
        continue
    
    # Empty lines
    if line.strip() == '':
        pdf.ln(2)
        i += 1
        continue
    
    # Bold lines (standalone like **File:**...)
    if line.strip().startswith('**') and '**' in line.strip()[2:]:
        text = clean_md(line.strip())
        pdf.set_font("Helvetica", "B", 9)
        pdf.set_text_color(30, 30, 30)
        pdf.set_x(10)
        pdf.multi_cell(pdf.w - 20, 5, text)
        pdf.set_font("Helvetica", "", 9)
        i += 1
        continue
    
    # Regular paragraph text
    text = clean_md(line.strip())
    if text:
        pdf.set_font("Helvetica", "", 9)
        pdf.set_text_color(30, 30, 30)
        pdf.set_x(10)
        pdf.multi_cell(pdf.w - 20, 5, text)
    
    i += 1

pdf.output(OUTPUT)
print(f"PDF saved to: {OUTPUT}")
print(f"Pages: {pdf.page_no()}")
