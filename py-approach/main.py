import markdown
import pdfkit

def markdown_to_pdf(md_file, pdf_file):
    # Read the Markdown file
    with open(md_file, "r", encoding="utf-8") as f:
        md_content = f.read()

    # Convert Markdown to HTML
    html_content = markdown.markdown(md_content)

    # Convert HTML to PDF
    pdfkit.from_string(html_content, pdf_file)

    print(f"Converted '{md_file}' to '{pdf_file}' successfully.")

# Example usage
markdown_to_pdf("sample.md", "output.pdf")
