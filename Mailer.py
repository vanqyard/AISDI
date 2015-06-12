import sys
import getpass
import platform
import smtplib

from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

def send_mail(teacher,course,exersise_no,files):
    """ Prepares email in proper format, includes given files, uses current login as 'From' field. """
    to = "mszlenk@lab011.elka.pw.edu.pl"
    
    frm = getpass.getuser() + "@" + platform.node()
    if not frm.endswith(".pw.edu.pl"):
        frm += ".elka.pw.edu.pl"
    
    msg = MIMEMultipart()
    msg['Subject'] = str(exersise_no)+"@"+teacher+"@"+course
    msg['To'] = to
    msg['From'] = frm

    for f in files:
        ff = open(f,'r')
        text = MIMEText(ff.read(),"plain","utf-8")
        text.add_header('Content-Disposition', 'attachment', filename=f)
        msg.attach(text)

    s = smtplib.SMTP()
    s.connect()
    s.sendmail(frm,[to],msg.as_string())

    if teacher=="jmyrcha":
        to = "jmyrcha@lab011.elka.pw.edu.pl"
        msg['To'] = to
        s.sendmail(frm,[to],msg.as_string())

    if teacher=="wgrabski":
        to = "wgrabski@lab011.elka.pw.edu.pl"
        msg['To'] = to
        s.sendmail(frm,[to],msg.as_string())
    print ">"+teacher+"<"


def main():
    if len(sys.argv) < 5:
        print "Usage",sys.argv[0],"course exersise_number teacher file1 file2 ..."
        exit(1)

    send_mail(sys.argv[3],sys.argv[1],int(sys.argv[2]),sys.argv[4:])


if __name__ == "__main__":
    main()
