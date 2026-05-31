#include "services/teacher_service.h"

#include "repositories/teacher_repository.h"
#include "repositories/workload_repository.h"

namespace services
{
    OperationResult ValidateTeacher(const models::Teacher& teacher)
    {
        if (teacher.full_name.empty())
        {
            return OperationResult::Fail("ПIБ викладача не може бути порожнiм.");
        }

        if (teacher.digital_commission.empty())
        {
            return OperationResult::Fail("Цифрова комiсiя не може бути порожньою.");
        }

        if (teacher.quota == 0)
        {
            return OperationResult::Fail("Квота викладача повинна бути бiльше 0.");
        }

        return OperationResult::Ok();
    }

    OperationResult CanDeleteTeacher(unsigned short teacher_id)
    {
        if (!GetTeacherById(teacher_id).has_value())
        {
            return OperationResult::Fail("Викладача з таким Id не знайдено.");
        }

        if (HasWorkloadForTeacher(teacher_id))
        {
            return OperationResult::Fail("Неможливо видалити викладача: вiн використовується в навантаженнi.");
        }

        return OperationResult::Ok();
    }
}
